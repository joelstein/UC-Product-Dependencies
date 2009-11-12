<?php

/**
 * Configure module settings. 
 */
function uc_product_dependencies_settings_form(&$form_state) {
  
  $options = array();
  $results = db_query("SELECT field_name FROM {content_node_field} WHERE type = 'nodereference' ORDER BY field_name");
  while ($row = db_fetch_array($results)) {
    $options[$row['field_name']] = $row['field_name'];
  }
  
  $form['uc_product_dependencies_cck_field'] = array(
    '#type' => 'select',
    '#title' => 'CCK Node Reference Field',
    '#description' => t('The field used to store product dependencies.'),
    '#options' => $options,
    '#required' => true,
    '#default_value' => variable_get('uc_product_dependencies_cck_field', ''),
  );
  
  $form['uc_product_dependencies_behavior_type'] = array(
    '#type' => 'radios',
    '#title' => 'Location of Dependent Products',
    '#options' => array(
      0 => t('Dependent product must be in cart'),
      2 => t('Dependent product must have been purchased in a previous order'),
      1 => t('Dependent product must be in cart or have been purchased in a previous order'),
    ),
    '#description' => t('Where should the dependent product be? Note: Previous purchases can only be determined for authenticated users.'),
    '#required' => true,
    '#default_value' => variable_get('uc_product_dependencies_behavior_type', 1),
  );
  
  $options = array();
  $results = db_query("SELECT * FROM {uc_order_statuses} ORDER BY weight");
  while ($row = db_fetch_array($results)) {
    $options[$row['order_status_id']] = $row['title'];
  }
  $form['uc_product_dependencies_status_field'] = array(
    '#type' => 'select',
    '#title' => 'Previous Purchase Order Status',
    '#options' => $options,
    '#default_value' => variable_get('uc_product_dependencies_status_field', 'payment_received'),
    '#description' => t('When dealing with previous purchases, select the order status used to determine if a product was purchased or not.'),
  );
  
  return system_settings_form($form);
}
