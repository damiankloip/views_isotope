<?php

/**
 * @file
 */

/**
 * @todo.
 */
class views_isotope_style_plugin extends views_plugin_style {

    protected $plugin_data = array();

  /**
   * Overrides views_plugin_style::init().
   */
  function init(&$view, &$display, $options = NULL) {
    parent::init($view, $display, $options);
  }

  /**
   * Overrides views_plugin_Style::get_row_class().
   */
  function get_row_class($row_index) {
    if ($this->uses_row_class()) {
      $class = $this->options['row_class'];
      if ($this->uses_fields() && $this->view->field) {
        $class = strip_tags($this->tokenize_value($class, $row_index));
      }

      $classes = explode(' ', $class);
      foreach ($classes as &$class) {
        $class = drupal_clean_css_identifier($class);
      }

      foreach ($this->plugin_data as $type => $handlers) {
        foreach ($handlers as $handler => $data) {
          if (isset($this->view->result[$row_index]->{$data['alias']})) {
            $classes[] = drupal_clean_css_identifier($data['alias'] . '--' . $this->view->result[$row_index]->{$data['alias']});
          }
        }
      }

      return implode(' ', $classes);
    }
  }

  /**
   * Overrides views_plugin_style::query().
   */
  function query() {
    parent::query();

    // Add any filter or sort exposed plugin fields to the query so we can use
    // this in row classes.
    $plugins = array('filter', 'sort');
    foreach ($plugins as $type) {
      foreach ($this->view->{$type} as $plugin) {
        if ($plugin->can_expose() && $plugin->is_exposed()) {
          $this->plugin_data[$type][$plugin->definition['handler']] = array(
            'table' => $plugin->table,
            'field' => $plugin->field,
            'alias' => $this->view->query->add_field($plugin->table, $plugin->field),
          );
        }
      }
    }
  }

}
