;;;
;; Copyright (C) 2014 Curtis Blumer
;;
;; This program is free software; you can redistribute it and/or
;; modify it under the terms of the GNU General Public License
;; as published by the Free Software Foundation; either version 2
;; of the License, or (at your option) any later version.
;;
;; This program is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.
;;
;; You should have received a copy of the GNU General Public License
; along with this program; if not, write to the Free Software
;; Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
;;;

api = 2
core = 7.x

;; Download Drupal and the Responsive Bartik theme

;projects[] = "drupal"
projects[responsive_bartik][version] = "1"

;;;
;; Custom modules
;;;

; Download installation profile locally
projects[curtapedia_profile][type] = "module"
projects[curtapedia_profile][download][type] = "git"
projects[curtapedia_profile][download][url] = "file:///home/cblumer/Development/curtapedia_security/.git"
projects[curtapedia_profile][download][branch] = "master"

; Download installation profile for GitHub
;projects[curtapedia_profile][type] = "profile"
;projects[curtapedia_profile][download][type] = "git"
;projects[curtapedia_profile][download][url] = "https://github.com/cblumer88/curtapedia_security.git"
;projects[curtapedia_profile][download][branch] = "master"

;;;
;; Contributed modules
;;;

;; Modules included or superceded by Drupal 8 ;;

projects[admin_language][version] = "1"
projects[admin_language][subdir] = "contrib"

projects[admin_views][version] = "1"
projects[admin_views][subdir] = "contrib"

projects[bean][version] = "1"
projects[bean][subdir] = "contrib"

projects[breakpoints][version] = "1"
projects[breakpoints][subdir] = "contrib"

projects[caption_filter][version] = "1"
projects[caption_filter][subdir] = "contrib"

projects[ctools][version] = "1"
projects[ctools][subdir] = "contrib"

projects[date][version] = "2"
projects[date][subdir] = "contrib"

projects[date_popup_authored][version] = "1"
projects[date_popup_authored][subdir] = "contrib"

projects[ds][version] = "2"
projects[ds][subdir] = "contrib"

projects[email][version] = "2"
projects[email][subdir] = "contrib"

projects[entity][version] = "1"
projects[entity][subdir] = "contrib"

projects[entitycache][version] = "1"
projects[entitycache][subdir] = "contrib"

projects[entityreference][version] = "1"
projects[entityreference][subdir] = "contrib"

projects[entity_translation][version] = "1"
projects[entity_translation][subdir] = "contrib"

projects[entity_view_mode][version] = "1"
projects[entity_view_mode][subdir] = "contrib"

projects[fallback_language_negotation][version] = "1"
projects[fallback_language_negotation][subdir] = "contrib"

projects[features][version] = "1"
projects[features][subdir] = "contrib"

projects[filter_perms][version] = "1"
projects[filter_perms][subdir] = "contrib"

projects[hidden_field][version] = "1"
projects[hidden_field][subdir] = "contrib"

projects[i18n][version] = "1"
projects[i18n][subdir] = "contrib"

projects[l10n_update][version] = "2"
projects[l10n_update][subdir] = "contrib"

projects[link][version] = "1"
projects[link][subdir] = "contrib"

projects[magic][version] = "2"
projects[magic][subdir] = "contrib"

projects[migrate][version] = "2.5"
projects[migrate][subdir] = "contrib"

projects[module_filter][version] = "2"
projects[module_filter][subdir] = "contrib"

projects[picture][version] = "2"
projects[picture][subdir] = "contrib"

projects[restws][version] = "2"
projects[restws][subdir] = "contrib"

projects[rules][version] = "2"
projects[rules][subdir] = "contrib"

projects[save_draft][version] = "1"
projects[save_draft][subdir] = "contrib"

projects[stringoverrides][version] = "1"
projects[stringoverrides][subdir] = "contrib"

projects[telephone][version] = "1"
projects[telephone][subdir] = "contrib"

projects[title][version] = "1"
projects[title][subdir] = "contrib"

projects[token][version] = "1"
projects[token][subdir] = "contrib"

projects[transliteration][version] = "3"
projects[transliteration][subdir] = "contrib"

projects[user_picture_field][version] = "1"
projects[user_picture_field][subdir] = "contrib"

projects[uuid][version] = "1"
projects[uuid][subdir] = "contrib"

projects[variable][version] = "2"
projects[variable][subdir] = "contrib"

projects[views][version] = "3"
projects[views][subdir] = "contrib"

projects[views_bulk_operations][version] = "3"
projects[views_bulk_operations][subdir] = "contrib"


;; Viniculum 1.x allows for Trackbacks and Pingbacks
;; Patches clean up code and add support for Rules
;projects[viniculum][type] = "module"
;projects[viniculum][subdir] = "patched"
;projects[viniculum][download][url] = "https://git.drupal.org/project/vinculum.git"
;projects[viniculum][download][branch] = "7.x-1.x"
;projects[viniculum][download][revision] = "a91754ad118504f414d2fcc54315830845475666"
;projects[viniculum][patch][] = "https://www.drupal.org/files/issues/continue-queue_0.patch"
;projects[viniculum][patch][] = "https://www.drupal.org/files/vinculum_rules_0.patch"

;; Viniculum 2.x allows for Trackbacks, Pingbacks, and WebMentions ;;
projects[viniculum][type] = "module"
projects[viniculum][download][url] = "https://github.com/sanduhrs/vinculum.git"
projects[viniculum][download][branch] = "7.x-2.x"
projects[viniculum][download][revision] = "a91754ad118504f414d2fcc54315830845475666"
projects[viniculum][subdir] = "contrib-git"


;; Essentials modules

projects[autosave][version] = "1"
projects[autosave][subdir] = "contrib"

projects[globalredirect][version] = "1"
projects[globalredirect][subdir] = "contrib"

projects[libraries][version] = "2"
projects[libraries][subdir] = "contrib"

projects[pathauto][version] = "2"
projects[pathauto][subdir] = "contrib"

projects[redirect][version] = "1"
projects[redirect][subdir] = "contrib"


;; UUID-related modules
;;
;; UUIDs, or Univerally Unique Identifiers, allow references to be made on sites
;; that are developed, staged, and pushed in a CI environment.

projects[uuidrole][version] = "1"
projects[uuidrole][subdir] = "contrib"

projects[uuid_features][version] = "1"
projects[uuid_features][subdir] = "contrib"

projects[uuid_redirect][version] = "1"
projects[uuid_redirect][subdir] = "contrib"

;projects[uuid_path][type] = "module"
;projects[uuid_path][download][type] = "git"
;projects[uuid_path][download][url] = "https://git.drupal.org/sandbox/jmorahan/1346170.git"
;projects[uuid_path][download][branch] = "7.x-1.x"
;projects[uuid_path][download][revision] = "1c9b95a4db95e7f2c6fe8d5291a0f45157964dd2"
;projects[uuid_path][subdir] = "contrib-git"

;; HTML5 modules
;;
;; Makes Drupal 7 more "HTML5-friendly"

projects[elements][version] = "1"
projects[elements][subdir] = "contrib"

projects[field_placeholder][version] = "3"
projects[field_placeholder][subdir] = "contrib"

projects[placeholder][version] = "3"
projects[placeholder][subdir] = "contrib"


;; Media modules
;;
;; These simplify the current mess that is Drupal media management

projects[colorbox][version] = "2"
projects[colorbox][subdir] = "contrib"

projects[file_entity][version] = "2"
projects[file_entity][subdir] = "contrib"

projects[media][version] = "2.0-alpha4"
projects[media][subdir] = "contrib"

projects[mediaelement][version] = "1"
projects[mediaelement][subdir] = "contrib"

projects[media_colorbox][version] = "1"
projects[media_colorbox][subdir] = "contrib"

projects[plupload][version] = "1"
projects[plupload][subdir] = "contrib"


;; User experience (UX) modules
;;
;; These are useful in easing the users experience while using Drupal.

projects[ckeditor][version] = "1.16"
projects[ckeditor][subdir] = "patched"
projects[ckeditor][patch][] = "https://www.drupal.org/files/issues/ckeditor-media_alt_title-2027287-4.patch"
projects[ckeditor][patch][] = "https://www.drupal.org/files/issues/ckeditor-admin-css-images-2323149-1.patch"
projects[ckeditor][patch][] = "https://www.drupal.org/files/issues/ckeditor-area-height-1154730-29.patch"
projects[ckeditor][patch][] = "https://www.drupal.org/files/issues/ckeditor-219995-jQuery_browser_test_deprecated-2.patch"
projects[ckeditor][patch][] = "https://www.drupal.org/files/issues/2324383-Toolbar_in_Ckeditor_profile_is_not_saved-1.patch"
projects[ckeditor][patch][] = "https://www.drupal.org/files/issues/ckeditor--teaser-break-paragraph-1217352-18.patch"

projects[logintoboggan][version] = "1"
projects[logintoboggan][subdir] = "contrib"

projects[navbar][version] = "1"
projects[navbar][subdir] = "contrib"

projects[password_tab][version] = "1"
projects[password_tab][subdir] = "contrib"

projects[quickedit][version] = "1"
projects[quickedit][subdir] = "contrib"


;; Administrator experience (AX) modules
;;
;; Modules that help sie administrators manage users more effectively.

projects[email_confirm][version] = "1"
projects[email_confirm][subdir] = "contrib"

projects[email_registration][version] = "1"
projects[email_registration][subdir] = "contrib"


;;; Libraries
;;;
;;; These are 3rd-party libraries download from other sources.

;; CKEditor Full (ckeditor)

libraries[ckeditor][download][type] = "git"
libraries[ckeditor][download][url] = "https://github.com/ckeditor/ckeditor-releases.git"
libraries[ckeditor][directory_name] = "ckeditor"
libraries[ckeditor][type] = "library"


;; Mobile Friendly Navigation Toolar (navbar)

; Underscore.js
libraries[underscore.js][download][type] = "file"
libraries[underscore.js][download][url] = "https://raw.githubusercontent.com/jashkenas/underscore/1.7.0/underscore.js"
libraries[underscore.js][directory_name] = "underscore"
libraries[underscore.js][type] = "library"

libraries[underscore-min.js][download][type] = "file"
libraries[underscore-min.js][download][url] = "https://raw.githubusercontent.com/jashkenas/underscore/1.7.0/underscore-min.js"
libraries[underscore-min.js][directory_name] = "underscore"
libraries[underscore-min.js][type] = "library"

libraries[underscore-min.map][download][type] = "file"
libraries[underscore-min.map][download][url] = "https://raw.githubusercontent.com/jashkenas/underscore/1.7.0/underscore-min.map"
libraries[underscore-min.map][directory_name] = "underscore"
libraries[underscore-min.map][type] = "library"

; Backbone.js
libraries[backbone.js][download][type] = "file"
libraries[backbone.js][download][url] = "https://raw.githubusercontent.com/jashkenas/backbone/1.1.2/backbone.js"
libraries[backbone.js][directory_name] = "backbone"
libraries[backbone.js][type] = "library"

libraries[backbone-min.js][download][type] = "file"
libraries[backbone-min.js][download][url] = "https://raw.githubusercontent.com/jashkenas/backbone/1.1.2/backbone-min.js"
libraries[backbone-min.js][directory_name] = "backbone"
libraries[backbone-min.js][type] = "library"

libraries[backbone-min.map][download][type] = "file"
libraries[backbone-min.map][download][url] = "https://raw.githubusercontent.com/jashkenas/backbone/1.1.2/backbone-min.map"
libraries[backbone-min.map][directory_name] = "backbone"
libraries[backbone-min.map][type] = "library"

; Modernizr.js
libraries[modernizr.js][download][type] = "file"
libraries[modernizr.js][download][url] = "https://raw.githubusercontent.com/Modernizr/Modernizr/v2.8.3/modernizr.js"
libraries[modernizr.js][directory_name] = "modernizr"
libraries[modernizr.js][type] = "library"
