<?php

function curtapedia_profile_default_password_policy_alter(&$policies) {
    // Create an 'Default' password policy for all roles.
    $config = array(
        'alpha_count' => array(
            'alpha_count' => '1',
        ),
        'char_count' => array(
            'char_count' => '6',
        ),
        'consecutive' => array(
            'consecutive_char_count' => '3',
        ),
        'delay' => array(
            'delay' => '1 day',
        ),
        'expire' => array(
            'expire_limit' => '2 years',
            'expire_warning_email_sent' => '-2 weeks, -1 week, -3 days, -1 day, -3 hours',
            'expire_warning_email_message' => 'This is a warning message',
            'expire_warning_email_subject' => '[user:name] you password on [site:name] shall expire in [password_expiration_date:interval] ',
        ),
        'int_count' => array(
            'int_count' => '1',
        ),
        'past_passwords' => array(
            'past_passwords' => '1',
        ),
        'role' => array(
            'roles' => array(
                '2' => TRUE,
            ),
        ),
        'username' => array(
            'username' => TRUE,
        ),
    );

    $password_policy = new stdClass();
    $password_policy->disabled = FALSE;
    $password_policy->api_version = 1;
    $password_policy->name = 'Default';
    $password_policy->config = serialize($config);
    $policies['Default'] = $password_policy;

    // Create an 'Elevated' password policy for 'Site architect' role.
    $config = array(
        'alpha_count' => array(
            'alpha_count' => '1',
        ),
        'char_count' => array(
            'char_count' => '8',
        ),
        'consecutive' => array(
            'consecutive_char_count' => '3',
        ),
        'delay' => array(
            'delay' => '3 days',
        ),
        'expire' => array(
            'expire_limit' => '2 years',
            'expire_warning_email_sent' => '-2 weeks, -1 week, -3 days, -1 day, -3 hours',
            'expire_warning_email_message' => 'This is a warning message',
            'expire_warning_email_subject' => '[user:name] you password on [site:name] shall expire in [password_expiration_date:interval] ',
        ),
        'int_count' => array(
            'int_count' => '1',
        ),
        'past_passwords' => array(
            'past_passwords' => '2',
        ),
        'role' => array(
            'roles' => array(
                '3' => TRUE,
            ),
        ),
        'symbol_count' => array(
            'symbol_count' => '1',
            'symbol_count_symbols' => '!@#$%^&*()_+=-|}{"?:><,./;\'\\[]',
        ),
        'username' => array(
            'username' => TRUE,
        ),
    );

    $password_policy = new stdClass();
    $password_policy->disabled = FALSE;
    $password_policy->api_version = 1;
    $password_policy->name = 'Elevated';
    $password_policy->config = serialize($config);
    $policies['elevated'] = $password_policy;

    //unset($config, $password_policy, $policies);
}
