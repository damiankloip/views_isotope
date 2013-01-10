<?php

/**
 * Implements hook_views_plugins().
 */
function views_isotope_views_plugins() {
  return array(
    'style' => array(
      'isotope' => array(
        'title' => t('Isotope'),
        'help' => t('Display using isotope.'),
        'handler' => 'views_isotope_style_plugin',
        'theme' => 'views_isotope_view',
        'uses fields' => FALSE,
        'uses row plugin' => TRUE,
        'uses row class' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
      ),
    ),
  );
}
