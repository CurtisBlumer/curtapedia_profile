<?php
/**
 * Enables modules and site configuration for a standard site installation
 * 
 * @author cblumer88
 * @copyright 2014 Curtis Blumer
 * @license http://www.gnu.org/licenses/gpl-3.0.html
 * @version 1.0
 */

/**
 * Implements hook_form_FORM_ID_alter() for install_configure_form().
 *
 * Allows the profile to alter the site configuration form.
 */
function curtapedia_profile_form_install_configure_form_alter(&$form, $form_state) {
  $server_name = filter_input(INPUT_SERVER, 'SERVER_NAME', FILTER_SANITIZE_URL);
  // Pre-populate the site name with the server name.
  $form['site_information']['site_name']['#default_value'] = $server_name;
  $form['site_information']['site_mail']['#default_value'] = 'do-not-reply@' . $server_name;
  $form['server_settings']['site_default_country']['#default_value'] = 'US';
  $form['update_notifications']['update_status_module'][2]['#default_value'] = 0;
  if ($server_name == 'dev.curtapedia.com') {
    $form['admin_account']['account']['name']['#default_value'] = 'root';
    $form['admin_account']['account']['mail']['#default_value'] = 'do-not-reply@' . $server_name;
  }
}

/**
 * Create post-configuration install tasks.
 * 
 * @return array $tasks
 */
function curtapedia_profile_install_tasks() {
  $tasks['curtapedia_profile_module_enable_curtapedia_d8'] = array(
    'display_name' => st('Drupal 8-ifying your site'),
    'type' => 'batch',
    'function' => '_curtapedia_profile_install_additional_modules'
  );
  $tasks['curtapedia_profile_user_settings_install'] = array(
    'display_name' => st('Setting up roles and permissions'),
    'type' => 'batch',
    'function' => '_curtapedia_profile_user_settings_install'
  );
  return $tasks;
}

/**
 * Install default user settings.
 * 
 * @return array $batch
 */
function _curtapedia_profile_user_settings_install() {
  // Create admin role.
  $operations[] = array('_curtapedia_profile_user_settings_role_admin_create', array());
  
// Load permissions include file.
  if(_curtapedia_profile_load_include('inc', 'includes/curtapedia_profile.permissions')) {
    $roles = _curtapedia_profile_user_settings_roles_define();

    // Loop through roles and find default permissions.
    foreach($roles as $index => $role) {
      $weight = 10 - $index; // Fixes weighting problem with ordering by most powerful account.
      $operations[] = array('_curtapedia_profile_user_settings_role_save', array($role, $weight, &$context));
    }
  } else {
    drupal_set_message("Couldn't load includes/curtapedia_profile.permisssions.inc",  'error');
    exit();
  }
  
  $operations[] = array('_curtapedia_profile_user_settings_flush_cache', array('Flushing website caches.'));

  $batch = array(
    'title' => t('Setting up default user roles and permissions'),
    'operations' => $operations,
    'file' => drupal_get_path('profile', 'curtapedia_profile') . '/includes/curtapedia_profile.permissions.inc',
  );

  return $batch;
}

/**
 * Install additional modules.
 * 
 * @return array $batch
 */
function _curtapedia_profile_install_additional_modules() {
  $modules[] = "curtapedia_d8";
  // Resolve the dependencies now, so that module_enable() doesn't need
  // to do it later for each individual module (which kills performance).
  $files = system_rebuild_module_data();
  foreach ($modules as $module) {
    if ($files[$module]->requires) {
      // Create a list of dependencies that haven't been installed yet.
      $module_requires = array_keys($files[$module]->requires);
      $dependencies = array_filter($module_requires, '_curtapedia_profile_filter_dependencies');
      // Add them to the module list.
      $modules = array_merge($modules, $dependencies);
    }
  }
  $modules = array_unique($modules);
  foreach ($modules as $module) {
    $modules_sorted[$module] = $files[$module]->sort;
  }
  arsort($modules_sorted);

  foreach ($modules_sorted as $module => $weight) {
    $operations[] = array('_curtapedia_profile_enable_module', array($module, $files[$module]->info['name']));
  }
  
  $operations[] = array('_curtapedia_profile_flush_caches', array('Flushing website caches.'));

  $batch = array(
    'title' => t('Installing additional functionality'),
    'operations' => $operations,
    'file' => drupal_get_path('profile', 'curtapedia_profile') . '/curtapedia_profile.profile_callbacks.inc',
  );

  return $batch;
}

/**
 * array_filter() callback used to filter out already installed dependencies.
 * 
 * @uses module_exists()
 * 
 * @return boolean $dependency
 */
function _curtapedia_profile_filter_dependencies($dependency) {
  return !module_exists($dependency);
}

/**
 * Install additonal modules
 * 
 * @return string|boolean $file
 */
function _curtapedia_profile_load_include($type, $name) {
  if (function_exists('drupal_get_path')) {
    $file = DRUPAL_ROOT . '/' . drupal_get_path('profile', 'curtapedia_profile') . "/$name.$type";
    drupal_set_message($file, 'notice');
    if (is_file($file)) {
      require_once $file;
      return $file;
    }
  }
  return FALSE;
}