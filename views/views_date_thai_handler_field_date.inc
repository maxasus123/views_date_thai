<?php
/**
 * @file
 * Easy Social view handler.
 */

/**
 * Handler for displaying Easy Social share buttons in views.
 */
class views_date_thai_handler_field extends views_handler_field {
  function init(&$view, &$options) {
      parent::init($view, $options);
      // Declare additional fields to be loaded with a single query.
      // This way there's no need to node_load() on render().
      $this->additional_fields['nid'] = 'nid';
      $this->additional_fields['type'] = 'type';
      $this->additional_fields['created'] = 'created';
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['custom_date_format'] = array('default' => '');

    return $options;
  }

   function options_form(&$form, &$form_state) {
    
    $form['custom_date_format'] = array(
      '#type' => 'textfield',
      '#title' => t('Custom date format'),
      '#description' => t('If "Custom", see the <a href="@url" target="_blank">PHP manual</a> for date formats. Otherwise, enter the number of different time units to display, which defaults to 2.', array('@url' => 'http://php.net/manual/function.date.php')),
      '#default_value' => isset($this->options['custom_date_format']) ? $this->options['custom_date_format'] : '',
    );

     parent::options_form($form, $form_state);
   }

   function render($values) {
    $custom_format = $this->options['custom_date_format'];
     // Render your content.
    $node = new stdClass;
    $node->created = $values->{$this->aliases['created']};

     return views_date_thai_get_formatted_date($node->created,$custom_format);
  }
}