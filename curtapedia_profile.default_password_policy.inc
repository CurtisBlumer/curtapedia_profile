<?php

function curtapedia_profile_default_password_policy_alter(&$policies) {
    // Create an Array with settings common to all policies.    
    $settings_common = array();
    $settings_common['alpha_count'] = array('alpha_count' => '1');
    $settings_common['consecutive'] = array('consecutive_char_count' => '3');
    $settings_common['delay'] = array('delay' => '1 day');
    $settings_common['expire'] = array(
        'expire_limit' => '2 years',
        'expire_warning_email_sent' => '-2 weeks, -1 week, -3 days, -1 day, -3 hours',
        'expire_warning_email_message' => 'This is a warning message',
        'expire_warning_email_subject' => '[user:name] you password on [site:name] shall expire in [password_expiration_date:interval] ',
    );
    $settings_common['int_count'] = array('int_count' => '1');
    $settings_common['username'] = array('username' => TRUE);

    // Settings unique to 'Default' policy.
    $settings = array(
        'char_count' => array(
            'char_count' => '6',
        ),
        'consecutive' => array(
            'consecutive_char_count' => '3',
        ),
        'past_passwords' => array(
            'past_passwords' => '1',
        ),
        'role' => array(
            'roles' => array(
                '2' => TRUE, // Drupal default "authenticated user" role
            ),
        ),
    );

    // Merge common and unique settings.
    $settings = array_merge($settings_common, $settings);

    // Create 'Default' password policy.    
    $password_policy = new stdClass();
    $password_policy->disabled = FALSE;
    $password_policy->api_version = 1;
    $password_policy->name = 'Default';
    $password_policy->config = serialize($settings);
    $policies['Default'] = $password_policy;

    // Unset variables to be used again. Not strictly necessary.
    unset($settings, $password_policy);

    // Settings unique to 'Elevated'.
    $settings = array(
        'char_count' => array(
            'char_count' => '8',
        ),
        'past_passwords' => array(
            'past_passwords' => '2',
        ),
        'role' => array(
            'roles' => array(
                '3' => TRUE, // Drupal 'Site architect' role created during install
            ),
        ),
        'symbol_count' => array(
            'symbol_count' => '1',
            'symbol_count_symbols' => '!@#$%^&*()_+=-|}{"?:><,./;\'\\[]',
        ),
    );
    // Merge common and unique settings.
    $settings = array_merge($settings_common, $settings);

    // Create 'Elevated' password policy. 
    $password_policy = new stdClass();
    $password_policy->disabled = FALSE;
    $password_policy->api_version = 1;
    $password_policy->name = 'Elevated';
    $password_policy->config = serialize($settings);
    $policies['Elevated'] = $password_policy;

    // Clean up used variables. Not strictly necessary.
    unset($settings, $settings_common, $password_policy);
}
