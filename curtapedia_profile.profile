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

function curtapedia_profile_default_password_policy_alter(&$policies) {
  // Only display this policy if no other policies are defined.
  $config = array(
    'alpha_count' => array(
      'alpha_count' => '1',
    ),
    'char_count' => array(
      'char_count' => '8',
    ),
    'consecutive' => array(
      'consecutive_char_count' => '',
    ),
    'int_count' => array(
      'int_count' => '1',
    ),
    'past_passwords' => array(
      'past_passwords' => '3',
    ),
    'symbol_count' => array(
      'symbol_count' => 1,
      'symbol_count_symbols' => '!@#$%^&*()_+=-|}{"?:><,./;\'\\[]',
    ),
    'username' => array(
      'enabled' => FALSE,
    ),
    'role' => array(
      'roles' => array(
        2 => 1,
        3 => 1,
      ),
    ),
    'expire' => array(
      'expire_limit' => '0',
      'expire_warning_email_sent' => '-14 days',
      'expire_warning_email_message' => '',
      'expire_warning_email_subject' => '[user:name] you password on [site:name] shall expire in [password_expiration_date:interval] ',
    ),
  );

  $password_policy = new stdClass();
  $password_policy->disabled = FALSE;
  $password_policy->api_version = 1;
  $password_policy->name = 'Default';
  $password_policy->config = serialize($config);
  $policies['Default policy'] = $password_policy;
}
