<?php

/**
 * Implements hook_field_formatter_info().
 */
function field_embed_views_field_formatter_info() {
  return array(
    'field_embed_views_default' => array(
      'label' => t('Default'),
      'field types' => array('field_embed_views')
    ),
  );
}

/**
 * Formats a field_embed_views.
 */
function theme_field_embed_views_formatter_default($variables) {
  $element = $variables['element'];
  $exposed_filters = $element['#settings'];
  $settings = $element['#settings'];

  //$settings = array();

  $display_id = $settings['display_id'];
  $view_name = $settings['view_name'];
  $view = $element['#view'];


  /*//disable all exposed filters
  $view->display_handler->set_option('exposed_block', TRUE);
  */

  $views_output = field_embed_views_prepare_view_for_element($view, $display_id, $settings, $output_html = TRUE);

  return $views_output;
}

/**
 * Implements hook_field_formatter_view().
 */
function field_embed_views_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {

  $instance_settings = $instance['settings'];

  list($entity_id) = entity_extract_ids($entity_type, $entity);
  $elements = array();

  switch ($display['type']) {
    case 'field_embed_views_default':
      foreach ($items as $delta => $item) {


        $view = views_get_view($instance_settings['view_name']);
        $elements[$delta] = array(
          '#type' => 'field_embed_views',
          '#theme' => 'field_embed_views_formatter_default',
          '#access' => $view && $view->access($instance_settings['display_name']),
          '#view' => $view,

          '#view_name' => $instance_settings['view_name'],
          '#view_display' => $instance_settings['display_name'],
          '#settings' => $item['settings'],
          '#entity_type' => $entity_type,
          '#entity_id' => $entity_id,
          '#entity' => $entity,
          '#element'
        );

      }
      break;
  }

  return $elements;
}