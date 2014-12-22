<?php

// Define settings array for 'Default' policy
function _curtapedia_profile_default_password_policy_settings_policy_default() {
    $settings = array();
    $settings['char_count']['char_count'] = '6'; // Minimum number of characters
    $settings['past_passwords']['past_passwords'] = '1'; // Number of past passwords to block from use
    $settings['role']['roles']['1'] = '0'; // No "anonymous" role
    $settings['role']['roles']['2'] = '2'; // Yes "authenticated user" role
    $settings['role']['roles']['3'] = '0'; // No 'Site architect' role (created during install)
    $settings = _curtapedia_profile_default_password_policy_settings_combine($settings);
    //drupal_set_message(t('@function function run. Default policy settings array created.', array('@function' => __FUNCTION__)), 'notice');
    return($settings);
}

// Define settings array for 'Elevated' policy
function _curtapedia_profile_default_password_policy_settings_policy_elevated() {
    // Declare variable as array
    $settings = array();
    $settings['char_count']['char_count'] = '8'; // Minimum number of characters
    $settings['past_passwords']['past_passwords'] = '2'; // Number of past passwords to block from use
    $settings['role']['roles']['1'] = '0'; // No "anonymous" role
    $settings['role']['roles']['2'] = '0'; // No "authenticated user" role
    $settings['role']['roles']['3'] = '3'; // Yes 'Site architect' role (created during install)
    $settings['symbol_count']['symbol_count'] = '1';
    $settings['symbol_count']['symbol_count_symbols'] = '!@#$%^&*()_+=-|}{"?:><,./;\'\\[]';
    $settings = _curtapedia_profile_default_password_policy_settings_combine($settings);
    //drupal_set_message(t('@function function run. Elevated policy settings array created.', array('@function' => __FUNCTION__)), 'notice');
    return($settings);
}

// Define settings array for password policy settings common to all polcies
function _curtapedia_profile_default_password_policy_settings_policy_common() {
    $settings = array();
    $settings['alpha_count']['alpha_count'] = '2'; // Minimum of 2 letters
    $settings['consecutive']['consecutive_char_count'] = '3'; // No more than 3 consecutive characters
    $settings['delay']['delay'] = '1 day'; // Password change only 1 time per day
    $settings['expire']['expire_limit'] = '2 years'; // Password expires every 2 years
    $settings['expire']['expire_warning_message'] = 'Your password has expired, it must be changed immediately.';
    $settings['expire']['expire_warning_email_sent'] = '-2 weeks, -1 week, -3 days, -1 day, -3 hours';
    $settings['expire']['expire_warning_email_message'] = 'This is a warning message';
    $settings['expire']['expire_warning_email_subject'] = '[user:name] you password on [site:name] shall expire in [password_expiration_date:interval]';
    $settings['int_count']['int_count'] = '1'; // Minimum of 1 number.
    $settings['username']['username'] = TRUE; // Do not allow username in password
    //drupal_set_message(t('@function function run. Common settings array created.', array('@function' => __FUNCTION__)), 'notice');
    return($settings);
}

// Create Password Policies
function curtapedia_profile_default_password_policy_alter(&$policies) {
    //Create 'Default' password policy
    $settings = _curtapedia_profile_default_password_policy_settings_policy_default();
    $password_policy = new stdClass();
    $password_policy->disabled = FALSE;
    $password_policy->api_version = 1;
    $password_policy->name = 'Default';
    $password_policy->config = serialize($settings);
    $policies['Default'] = $password_policy;

    // Create 'Elevated' password policy
    $settings = _curtapedia_profile_default_password_policy_settings_policy_elevated();
    $password_policy = new stdClass();
    $password_policy->disabled = FALSE;
    $password_policy->api_version = 1;
    $password_policy->name = 'Elevated';
    $password_policy->config = serialize($settings);
    $policies['Elevated'] = $password_policy;
    //drupal_set_message(t('@function function run. Password policies added.', array('@function' => __FUNCTION__)), 'notice');
}

// Combine common and unique settings arrays
function _curtapedia_profile_default_password_policy_settings_combine(array $settings) {
    $settings = array_merge($settings, _curtapedia_profile_default_password_policy_settings_policy_common());
    //drupal_set_message(t('@function function run. Arrays merged.', array('@function' => __FUNCTION__)), 'notice');
    return($settings);
}
