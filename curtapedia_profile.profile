<?php
/**
 * @file
 * Enables modules and site configuration for a standard site installation.
 */

/**
 * Implements hook_form_FORM_ID_alter() for install_configure_form().
 *
 * Allows the profile to alter the site configuration form.
 */
function curtapedia_profile_form_install_configure_form_alter(&$form, $form_state) {
  // Pre-populate the site name with the server name.
  $form['site_information']['site_name']['#default_value'] = $_SERVER['SERVER_NAME'];
  $form['site_information']['site_mail']['#default_value'] = 'do-not-reply@' . $_SERVER['SERVER_NAME'];
  $form['server_settings']['site_default_country']['#default_value'] = 'US';
  $form['update_notifications']['update_status_module'][2]['#default_value'] = 0;
  if ($_SERVER['SERVER_NAME'] == 'dev.curtapedia.com') {
    $form['admin_account']['account']['name']['#default_value'] = 'root';
    $form['admin_account']['account']['mail']['#default_value'] = 'do-not-reply@' . $_SERVER['SERVER_NAME'];
  }
}

function curtapedia_profile_install_tasks() {
  $tasks['curtapedia_profile_module_enable_curtapedia_d8'] = array(
    'display_name' => st('Drupal 8-ifying your site'),
    'type' => 'batch',
    'function' => '_curtapedia_profile_install_additional_modules'
  );
  return $tasks;
}

function _curtapedia_profile_install_additional_modules() {
  global $install_state;
 
  $modules[] = "curtapedia_d8";
  // Resolve the dependencies now, so that module_enable() doesn't need
  // to do it later for each individual module (which kills performance).
  $files = system_rebuild_module_data();
  $modules_sorted = array();
  foreach ($modules as $module) {
    if ($files[$module]->requires) {
      // Create a list of dependencies that haven't been installed yet.
      $dependencies = array_keys($files[$module]->requires);
      $dependencies = array_filter($dependencies, '_curtapedia_profile_filter_dependencies');
      // Add them to the module list.
      $modules = array_merge($modules, $dependencies);
    }
  }
  $modules = array_unique($modules);
  foreach ($modules as $module) {
    $modules_sorted[$module] = $files[$module]->sort;
  }
  arsort($modules_sorted);

  $operations = array();

  foreach ($modules_sorted as $module => $weight) {
    $operations[] = array('_curtapedia_profile_enable_module', array($module, $files[$module]->info['name']));
  }
  
  $operations[] = array('_curtapedia_profile_flush_caches', array(t('Flushed caches.')));

  $batch = array(
    'title' => t('Installing additional functionality'),
    'operations' => $operations,
    'file' => drupal_get_path('profile', 'curtapedia_profile') . '/curtapedia_profile.profile_callbacks.inc',
  );

  return $batch;
}

/**
 * array_filter() callback used to filter out already installed dependencies.
 */
function _curtapedia_profile_filter_dependencies($dependency) {
  return !module_exists($dependency);
}