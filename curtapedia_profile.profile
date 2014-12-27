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

function curtapedia_profile_install_tasks($install_state) {
  $tasks['curtapedia_profile_module_enable_curtapedia_d8'] = array(
    'display_name' => st('Drupal 8-ifying your site'),
    'type' => 'batch',
    'function' => '_curtapedia_profile_install_additional_modules'
  );
  /*$tasks['curtapedia_security'] = array(
    'display_name' => st('Securing your site'),
    'type' => 'normal',
    'run' => INSTALL_TASK_RUN_IF_NOT_COMPLETED,
    'function' => '_curtapedia_profile_enable_curtapedia_security'
  );*/
  return $tasks;
}

function _curtapedia_profile_module_enable_curtapedia_security() {
  $module_list = array(
      'curtapedia_security',
  );
  module_enable($module_list, TRUE);
}

function _curtapedia_profile_install_additional_modules() {
  global $install_state;
  /*$install_demo_store = variable_get('commerce_kickstart_demo_store', FALSE);
  if ($install_demo_store) {
    $modules = array(
      'commerce_kickstart_reset',
      'commerce_kickstart_block',
      'commerce_kickstart_user',
      'commerce_checkout_redirect',
      'commerce_kickstart_social',
      'commerce_kickstart_product',
      'commerce_kickstart_product_ui',
      'commerce_kickstart_blog',
      'commerce_kickstart_slideshow',
      'commerce_kickstart_merchandising',
      'commerce_kickstart_menus',
      'commerce_kickstart_search',
      'commerce_kickstart_taxonomy',
    );
  }
  else {
    $modules = array(
      'commerce_kickstart_block',
      'commerce_kickstart_user',
      'commerce_kickstart_lite_product',
      'commerce_kickstart_product_ui',
      'commerce_kickstart_search',
      'commerce_kickstart_taxonomy',
    );
    $selected_extras = variable_get('commerce_kickstart_selected_extras', array());
    if (empty($selected_extras['anonymous_checkout'])) {
      $modules[] = 'commerce_checkout_redirect';
    }
    if (!empty($selected_extras['merchandising'])) {
      $modules[] = 'commerce_kickstart_merchandising';
    }
    if (!empty($selected_extras['slideshow'])) {
      $modules[] = 'commerce_kickstart_slideshow';
    }
    if (!empty($selected_extras['menus'])) {
      $modules[] = 'commerce_kickstart_menus';
    }
    if (!empty($selected_extras['blog'])) {
      $modules[] = 'commerce_kickstart_blog';
    }
    if (!empty($selected_extras['social'])) {
      $modules[] = 'commerce_kickstart_social';
    }
    if (!empty($selected_extras['zoom_cloud'])) {
      variable_set('commerce_kickstart_product_zoom_enabled', TRUE);
    }
  }

  $install_localization = variable_get('commerce_kickstart_localization', FALSE);
  if ($install_localization) {
    $modules[] = 'locale';
    $modules[] = 'variable';
    $modules[] = 'i18n';
    $modules[] = 'i18n_field';
  }

  $store_country = variable_get('commerce_kickstart_store_country', 'US');
  // Enable Payleap and Paypal for North America.
  if (in_array($store_country, array('CA', 'US'))) {
    $modules[] = 'commerce_payleap';
    $modules[] = 'commerce_payflow';
    $modules[] = 'commerce_paypal_ec';
  }
  // Enable the commerce_kickstart_dfp module.
  if ($install_state['parameters']['use_dfp']) {
    $modules[] = 'commerce_kickstart_dfp';
  }*/
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
  // Enable and set as default the correct theme.
  /*$theme = $install_demo_store ? 'commerce_kickstart_theme' : 'omega_kickstart';
  $operations[] = array('_commerce_kickstart_enable_theme', array($theme));*/
  // Enable the selected modules.
  foreach ($modules_sorted as $module => $weight) {
    $operations[] = array('_curtapedia_profile_enable_module', array($module, $files[$module]->info['name']));
  }
  /*if ($install_localization) {
    $operations[] = array('_commerce_kickstart_setup_localization', array(t('Configured localization.')));
  }*/
  $operations[] = array('_curtapedia_profile_flush_caches', array(t('Flushed caches.')));

  $batch = array(
    'title' => $install_demo_store ? t('Installing demo store') : t('Installing additional functionality'),
    'operations' => $operations,
    'file' => drupal_get_path('profile', 'curtapedia_profile') . '/curtapedia_profile.profile_callbacks.inc',
  );

  return $batch;
}

function _curtapedia_profile_module_enable_curtapedia_d8() {
  $module_list = array(
      'curtapedia_d8',
  );
  module_enable($module_list, TRUE);
}