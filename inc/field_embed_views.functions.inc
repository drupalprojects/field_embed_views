<?php

/**
 * in future this will be key function witch work with other function that setup view
 *
 * @param $view
 * @param $display_id
 * @param $settings
 */
/*
 */
function field_embed_views_prepare_view_for_element($view, $display_id, $settings, $output_html = FALSE) {

//TODO delete this from preparation section

  $view_name = $settings['view_name'];
  $view = views_get_view($view_name);

  /**
   * setting per page items
   */

  //TODO Pagination FLEXABILITY!! today didn't change type of pagination
  if (isset($settings['views_items_limit']['views_items_limit_enable'])) {
    $view->display[$display_id]->display_options['pager']['options']['items_per_page'] = $settings['views_items_limit']['views_items_limit_value'];
    $view->display[$display_id]->display_options['pager']['type'] = $settings['views_items_limit']['pager_type'];

  }

  $filters = $view->display[$display_id]->display_options['filters'];

  //Prepating visible filters list

  $visible_exposed_filters = array();
  $settings['views_filters']['visible_exposed_filters'] = array();
  foreach ($settings['views_filters']['visibility'] as $filter_name => $filter_value) {
    if ($filter_value) {
      $settings['views_filters']['visible_exposed_filters'][] = $filter_name;
    }
  }


  // Preparing usable filters list


  /*
   * load list of standart filter
   * standart filters - filters witch using in view without exposing. like type of object
  */
  foreach ($filters as $filter_name => $filter_value) {
    if (empty($filter_value['exposed']) || ($filter_value['exposed'] == FALSE)) {
      $settings['views_filters']['usable_exposed_filters'][] = $filter_name;
    }
  }



  //hiding sorts and set parameters to them
  foreach ($view->display[$display_id]->display_options['sorts'] as $sort_name => $sort_value) {
    if (isset($settings['views_sorts']['sort_by']) && ($settings['views_sorts']['sort_by'] == $sort_name)) {
      $view->display[$display_id]->display_options['sorts'][$sort_name]['order'] = $settings['views_sorts']['sort_order'];
      unset($view->display[$display_id]->display_options['sorts'][$sort_name]['exposed']);
    } else {
      unset($view->display[$display_id]->display_options['sorts'][$sort_name]);
    }
  }

  


  /*
   * getting list of filters,witch are used in view
   *
   */
  $settings['views_filters']['usable_exposed_filters'] = array('status', 'type');
  foreach ($settings['views_filters']['values'] as $filter_name => $filter_value) {
    if (empty($filter_value)) {
      continue;
    }
    if ($filter_value == 'All') {
      continue;
    }
    //   $view->exposed_input[$filter_name] = $filter_value;

    $settings['views_filters']['usable_exposed_filters'][] = $filter_name;
// setting filter value
    $view->display[$display_id]->display_options['filters'][$filter_name]['value']['value'] = $filter_value;
  }

  field_embed_views_showing_exposed_elements($view, $display_id, $filters, $settings['views_filters']['usable_exposed_filters'], $settings['views_filters']['visible_exposed_filters']);



  //$view->pre_execute();
  $view->execute();
  

  if ($output_html) {
    return $view->preview($display_id); // outputting html
  } else {
    return $view->result; //outputting items
  }


}

function field_embed_views_get_results($view,$display_id,$output_html=FALSE){

  $view->execute();

  if ($output_html) {
    return $view->preview($display_id); // outputting html
  } else {
    return $view->result; //outputting items
  }

}

function field_embed_views_get_count(&$view,$filters){
  foreach($filters as $filter_name => $filter_value){
    if ($filter_name = ''){

    }else{
      $view->display[$display_id]->display_options['filters'][$filter_name]['value']['value'] = $filter_value;
    }
  }

}