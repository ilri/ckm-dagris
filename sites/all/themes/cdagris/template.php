<?php

/**
 * @file
 * template.php
 */
function dagris_eth_preprocess_page(&$vars) {
  if(drupal_is_front_page()) {
    drupal_add_js(drupal_get_path('theme', 'cdagris') . '/js/skrollr.min.js');
    drupal_add_js(drupal_get_path('theme', 'cdagris') . '/js/front.js');
  }
}
