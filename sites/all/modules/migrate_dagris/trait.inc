<?php

/**
 * The TraitMigration uses the mi_node_traits table as source and
 * creates Drupal nodes of type 'Trait' as destination.
 */
class TraitMigration extends DagrisMigration {

    public function __construct() {
        // call parent constructor
        parent::__construct();

        // add a description
        $this->description = t('Trait migration');

        // add dependencies
        $this->dependencies = array('TraitType', 'BreedCountry', 'Bibliography', 'Sex', 'Contact' , 'ManagementCondition');

        // define query
        $query = Database::getConnection('default', 'dagris_migration')
            ->select('mi_node_traits', 'br')
            ->fields('br', array(
                'id',
                'breed_id',
                'trait_type_id',
                'breed_country_id',
                'bibliography_id',
                'sex_id',
                'contact_id',
                'management_condition_id',
                'identifier_value',
                'value',
                'age',
                'mean',
                'standard_deviation',
                'standard_error',
                'size',
                'comment',
                'management',
                'location'
            ));

        $this->source = new MigrateSourceSQL($query);
        $this->destination = new MigrateDestinationNode('trait');
        $this->map = new MigrateSQLMap($this->machineName, array(
                'id' => array(
                    'type' => 'int',
                    'unsigned' => TRUE,
                    'not null' => TRUE
                )
            ), MigrateDestinationNode::getKeySchema()
        );
        $this->addFieldMapping('title', 'identifier_value');
        $this->addFieldMapping('field_ref_tr_breed', 'breed_id')
            ->sourceMigration('Breed');
        $this->addFieldMapping('field_ref_tr_trait_type', 'trait_type_id')
            ->sourceMigration('TraitType');
        $this->addFieldMapping('field_ref_tr_breed_country', 'breed_country_id')
            ->sourceMigration('BreedCountry');
        $this->addFieldMapping('field_ref_tr_bibliography', 'bibliography_id')
            ->sourceMigration('Bibliography');
        $this->addFieldMapping('field_ref_tr_sex', 'sex_id')
            ->sourceMigration('Sex');
        $this->addFieldMapping('field_ref_tr_contact', 'contact_id')
            ->sourceMigration('Contact');
        $this->addFieldMapping('field_ref_tr_mc', 'management_condition_id')
            ->sourceMigration('ManagementCondition');
        $this->addFieldMapping('field_tr_value', 'value');
        $this->addFieldMapping('field_tr_age', 'age');
        $this->addFieldMapping('field_tr_mean', 'mean');
        $this->addFieldMapping('field_tr_standard_deviation', 'standard_deviation');
        $this->addFieldMapping('field_tr_standard_error', 'standard_error');
        $this->addFieldMapping('field_tr_size', 'size');
        $this->addFieldMapping('field_tr_comment', 'comment');
        $this->addFieldMapping('field_tr_management', 'management');
        $this->addFieldMapping('field_tr_location', 'location');
    }

    /**
     * Make sure there is value for the title destination field
     * and that the length of the string does not exceed 255
     * @param  [array] $current_row [The current row to be commited into the drupal database]
     * @return [boolean]              [Response to either to continue with adding the row or not]
     */
    public function prepareRow($current_row) {
        if(strlen($current_row->identifier_value) > 255){
            $current_row->identifier_value = substr($current_row->identifier_value, 0, 255);
        }
        if(!$current_row->identifier_value){
            $current_row->identifier_value = "Unspecified-" . time();
        }
        return TRUE;
    }

}
