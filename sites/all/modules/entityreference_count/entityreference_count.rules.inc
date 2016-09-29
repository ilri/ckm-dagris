<?php

/**
 * @file
 * Basic rules integration for entityreference_count module.
 */

/**
 * Implements hook_rules_event_info().
 */
function entityreference_count_rules_event_info() {
  $items = array();

  $items['entityreference_count_updated'] = array(
    'label' => t('EntityReference Count field updated'),
    'group' => t('EntityReference Count'),
    'variables' => array(
      'entity' => array(
        'type' => 'entity',
        'label' => t('Entity containing updated EntityReference Count field'),
      ),
    ),
  );

  return $items;
}
