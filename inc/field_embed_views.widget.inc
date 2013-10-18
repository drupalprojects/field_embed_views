<?php

/**
 * Implements hook_field_widget_info().
 */
function field_embed_views_field_widget_info() {
  return array(
    'field_embed_views' => array(
      'label' => 'Views Exposed Filters',
      'field types' => array('field_embed_views'),
    ),
  );
}

/**
 * Implements hook_field_widget_form().
 */
function field_embed_views_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {

  $view_name = $instance['settings']['view_name'];
  $display_name = $instance['settings']['display_name'];
  $view = views_get_view($view_name);


  /**
   * if $view_name not selected yet -> return elements;
   */
  if (empty($view_name)) {
    return $element;
  }

  if (empty($items[$delta])) {
    $items[$delta] = array();
  }


  $element += array(
    '#type' => $instance['widget']['type'],
    '#default_value' => isset($items[$delta]) ? $items[$delta] : '',
  );


  return $element;
}

/**
 * validation of filter list checkboxes
 *
 * limits count of checkboxes to 3 items
 */
function field_embed_views_checkbox_checked_limit_validate($element, &$form_state) {

  $element_count = 0;
  foreach ($element['#rows'] as $field_name => $row_line) {
    foreach ($row_line as $row_element) {
      if (isset($row_element['data']['#title'])) {
        if ($row_element['data']['#title'] == t('Public')) {

          $element_count++;
        }
      }
    }
  }

  if ($element_count > 3) {
    form_error($element, t('Only 3 filters can be published'));
  }
}