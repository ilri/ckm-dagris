<?php

/**
 * The ContactMigration uses the mi_node_breeds table as source and
 * creates Drupal nodes of type 'Contact' as destination.
 */
class ContactMigration extends DagrisMigration {

    public function __construct() {
        // call parent constructor
        parent::__construct();

        // add a description
        $this->description = t('Contact migration');

        // define query
        $query = Database::getConnection('default', 'dagris_migration')
            ->select('mi_node_contacts', 'ct')
            ->fields('ct', array(
                'id',
                'first_name',
                'last_name',
                'address',
                'city',
                'country',
                'phone',
                'fax',
                'email'
            ));

        $this->source = new MigrateSourceSQL($query);
        $this->destination = new MigrateDestinationNode('contact');
        $this->map = new MigrateSQLMap($this->machineName, array(
                'id' => array(
                    'type' => 'int',
                    'unsigned' => TRUE,
                    'not null' => TRUE
                )
            ), MigrateDestinationNode::getKeySchema()
        );
        $this->addFieldMapping('title', 'first_name');
        $this->addFieldMapping('field_ref_ct_country', 'country'); // This should be an Entity Reference
        $this->addFieldMapping('field_ct_last_name', 'last_name');
        $this->addFieldMapping('field_ct_address', 'address');
        $this->addFieldMapping('field_ct_city', 'city');
        $this->addFieldMapping('field_ct_phone', 'phone');
        $this->addFieldMapping('field_ct_fax', 'fax');
        $this->addFieldMapping('field_ct_email', 'email');
    }

    /**
     * Make sure there is value for the title destination field
     * and that the length of the string does not exceed 255
     * @param  [array] $current_row [The current row to be commited into the drupal database]
     * @return [boolean]              [Response to either to continue with adding the row or not]
     */
    public function prepareRow($current_row) {
        if(strlen($current_row->first_name) > 255){
            $current_row->first_name = substr($current_row->first_name, 0, 255);
        }
        if(!$current_row->first_name){
            $current_row->first_name = "Unspecified-" . time();
        }
        return TRUE;
    }

}
