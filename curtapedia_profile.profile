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
  $form['site_information']['site_mail']['#default_value'] = "do-not-reply@" . $_SERVER['SERVER_NAME'];
  $form['server_settings']['site_default_country']['#default_value'] = "US";
  $form['update_notifications']['update_status_module'][2]['#default_value'] = 0;
}

/**
 * Implements hook_ctools_plugin_api().
 */
function curtapedia_profile_ctools_plugin_api($module, $api) {
    if ($module == "password_policy" && $api == "default_password_policy") {
        return array("version" => "1");
    }

    module_load_include('inc', 'curtapedia_profile', 'includes/curtapedia_profile.default_password_policy');
}
