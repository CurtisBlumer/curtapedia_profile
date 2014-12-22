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
}

function _curtapedia_profile_no_file_exists($filename) {
    drupal_set_message(t('File "@filename" not found', array('@filename' => $filename)), 'error', TRUE);
}

function _curtapedia_profile_no_function_exists($function) {
    drupal_set_message(t('Function "@function" not found', array('@function' => $function)), 'error', TRUE);
    exit();
}

function curtapedia_profile_install_tasks($install_state) {
    $include_files = array();
    $include_files['password_profile'] = __DIR__ . '/includes/curtapedia_profile.password_policy.inc';
    foreach($include_files as $file) {
        $file_exists = (file_exists($file)) ? require_once($file) : _curtapedia_profile_no_file_exists($file);
    }

    // test functions
    $functions['hook_default_password_policy_alter'] = 'curtapedia_profile_default_password_policy_alter';
    foreach($functions as $function) {
        if(!function_exists($function)) {
            _curtapedia_profile_no_function_exists($function);
        }
    }

    $tasks['default_password_policy'] = array(
        'display_name' => st('Adding default Password Policies'),
        'type' => 'normal',
        'run' => INSTALL_TASK_RUN_IF_NOT_COMPLETED,
        'function' => 'curtapedia_profile_default_password_policy_alter'
    );
    return $tasks;
}
