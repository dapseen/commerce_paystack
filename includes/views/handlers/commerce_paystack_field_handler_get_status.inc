<?php
/**
 * @file
 * Field handler for getting the payment transaction from PayStack.
 */

/**
 * Handler for the requery link on an PayStack payment transaction.
 */
class commerce_paystack_field_handler_get_status extends views_handler_field {
  /**
   * Constructor.
   */
  public function construct() {
    parent::construct();

    $this->additional_fields['transaction_id'] = array('table' => 'commerce_payment_transaction', 'field' => 'transaction_id');
    $this->additional_fields['payment_method'] = array('table' => 'commerce_payment_transaction', 'field' => 'payment_method');
  }

  /**
   * Overridden query() method.
   */
  public function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  /**
   * Overridden render() method.
   */
  public function render($values) {
    $transaction_id = $this->get_value($values, 'transaction_id');
    $payment_method = $this->get_value($values, 'payment_method');

    // Render this only for PayStack payments.
    if ($payment_method == 'paystack_standard') {
      return l(t('Check status'), 'admin/paystack/look-up/nojs/' . $transaction_id, array('attributes' => array('class' => 'use-ajax')));
    }
    else {
      return '';
    }
  }

}