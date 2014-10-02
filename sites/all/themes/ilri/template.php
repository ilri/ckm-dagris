<?php

/**
 * @file
 * template.php
 */
function ilri_preprocess_page(&$vars) {
  if(drupal_is_front_page()) {
    drupal_add_js(drupal_get_path('theme', 'ilri') . '/js/skrollr.min.js');
    drupal_add_js(drupal_get_path('theme', 'ilri') . '/js/front.js');
  }
}
