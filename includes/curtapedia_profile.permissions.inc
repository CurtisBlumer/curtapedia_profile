<?php

/* 
 * Copyright (C) 2014 cblumer
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

/*
 * Define the Drupal Site Administrator role.
 * 
 * In Drupal the the Administrator Role is a bit of a misnomer given the average
 * site admin should not be able to access some of Drupal's advanced settings.
 * This should be called before '_curtapedia_profile_user_roles_define()'.
 * 
 * @return array
 * 
 * @todo Move permission configuration into install task.
*/
function _curtapedia_profile_user_roles_admininstrator_role_define() {
  $administrator_role['role'] = new stdClass();
  $administrator_role['role']->name = 'Site Architect';
  $administrator_role['role']->weight = 50;
  $administrator_role['permissions'] = array_keys(module_invoke_all('permission'));
  
  return $administrator_role;
}

/*
 * Save Drupal Administrator Role into the datatbase
 * 
 * Saves the Drupal Administrator Role into the database, assigns complete set 
 * of permissions, and assignes User 1 to that role.
 * 
 * @param array $administrator_role
 * 
 * @todo Move permission configuration into install task.
 */
function _curtapedia_profile_user_roles_admininstrator_role_save(array &$administrator_role) {
  user_role_save($administrator_role['role']);
  user_role_grant_permissions($administrator_role['role']->rid, $administrator_role['permissions']);

  //Assign User 1 the Drupal Administrator Role.
  db_insert('users_roles')
    ->fields(array(
      'uid' => 1,
      'rid' => $administrator_role['role']->rid,
      ))
    ->execute();
  
  // Set the role in the Variables table
  variable_set('user_admin_role', $administrator_role['role']->rid);
}

/* Define other Drupal user roles
 * 
 * Defines other Drupal 7 roles that parity WordPress roles. Roles must be 
 * defined after all the content types are created so that permssions may be 
 * properly assigned for them. This should be called last.
 * 
 * @return array
 * 
 * @todo Move permission configuration into install task.
*/
function _curtapedia_profile_user_roles_define() {
  $user_roles = array();
  $user_roles['site administrator']['role'] = new stdClass();
  $user_roles['site administrator']['role']->name = 'Site Administrator';
  $user_roles['site administrator']['role']->weight = 49;
  $user_roles['site administrator']['permissions'] = array(
    'administer blocks',
    'access content',
    //'access navbar',
    'access content overview',
    'administer nodes',
    'view own unpublished content',
    'view revisions',
    'revert revisions',
    'delete revisions',
    'administer themes',
    'access administration pages',
    'access site in maintenance mode',
    'access user profiles',
  );
  
  $user_roles['editor']['role'] = new stdClass();
  $user_roles['editor']['role']->name = 'Editor';
  $user_roles['editor']['role']->weight = 48;
  $user_roles['editor']['permissions'] = array(
    'access content',
    //'access navbar',
    'access content overview',
    'view own unpublished content',
    'view revisions',
    'revert revisions',
    'create page content',
    'edit any page content',
    'access user profiles',
  );

  $user_roles['author']['role'] = new stdClass();
  $user_roles['author']['role']->name = 'Author';
  $user_roles['author']['role']->weight = 47;
  $user_roles['author']['permissions'] = array(
    'access content',
    //'access navbar',
    'access content overview',
    'view own unpublished content',
    'view revisions',
    'create own page content',
    'edit own page content',
    'access user profiles',
  );

  $user_roles['contributor']['role'] = new stdClass();
  $user_roles['contributor']['role']->name = 'Contributor';
  $user_roles['contributor']['role']->weight = 46;
  $user_roles['contributor']['permissions'] = array(
    'access content',
    'view own unpublished content',
    'view revisions',
    'create own page content',
    'edit own page content',
    'access user profiles',
  );
  return (array)$user_roles;
}

/*
 * Save Drupal user roles into the datatbase
 * 
 * Saves other Drupal user roles and permissions into the database.
 * 
 * @todo Move permission configuration into install task.
 */
function _curtapedia_profile_user_roles_save(array &$user_roles) {
  foreach($user_roles as $user_role) {
    user_role_save($user_role['role']);
    user_role_grant_permissions($user_role['role']->rid, $user_role['permissions']);
  }
}