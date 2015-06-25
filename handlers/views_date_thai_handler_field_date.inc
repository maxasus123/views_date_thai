<?php
 
/**
 * A handler to display dates as just the time if today, otherwise as time and date.
 *
 * @ingroup views_field_handlers
 */
class views_date_thai_handler_field_date extends views_handler_field_date {
function option_definition() {
    $options = parent::option_definition();

    $options['thai_custom'] = array('default' => '');

    return $options;
  }
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['date_format']['#options']['thai_custom'] = t('Thai Custom');

    $form['thai_custom'] = array(
      '#type' => 'textfield',
      '#title' => t('Thai Custom date format'),
      '#description' => t('If "Custom", see the <a href="@url" target="_blank">PHP manual</a> for date formats. Otherwise, enter the number of different time units to display, which defaults to 2.', array('@url' => 'http://php.net/manual/function.date.php')),
      '#default_value' => isset($this->options['thai_custom']) ? $this->options['thai_custom'] : '',
      '#dependency' => array('edit-options-date-format' => array('thai_custom')),
    );

     
  }
    function render($values) {
    $value = $this->get_value($values);
    $format = $this->options['date_format'];
    $thai_format = $this->options['thai_custom'];
    // check for our custom format
    if ($format == 'thai_custom') {
      // check to see whether value is whithin today range
        // this value is older than today
        return views_date_thai_get_formatted_date($value, $thai_format);      
    }
    // otherwise render the date using the normal date handler
    else {
      return parent::render($values);
     }
   }
}