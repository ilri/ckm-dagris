<?php

/**
 * The TraitQuantitativeValueMigration uses the mi_node_trait_quantitative_values table as source and
 * creates Drupal nodes of type 'TraitQuantitativeValue' as destination.
 */
class TraitQuantitativeValueMigration extends DagrisMigration {

    public function __construct() {
        // call parent constructor
        parent::__construct();

        // add a description
        $this->description = t('Trait Quantitative Value migration');

        // add dependencies
        $this->dependencies = array('Trait');

        // define query
        $query = Database::getConnection('default', 'dagris_migration')
            ->select('mi_node_trait_quantitative_values', 'tqv')
            ->fields('tqv', array(
                'id',
                'trait_id',
                'mean',
                'standard_deviation',
                'standard_error',
                'size'
            ));

        $this->source = new MigrateSourceSQL($query);
        $this->destination = new MigrateDestinationNode('trait_quantitative_value');
        $this->map = new MigrateSQLMap($this->machineName, array(
                'id' => array(
                    'type' => 'int',
                    'unsigned' => TRUE,
                    'not null' => TRUE
                )
            ), MigrateDestinationNode::getKeySchema()
        );
        $this->addFieldMapping('title', 'size');
        $this->addFieldMapping('field_ref_tqv_trait', 'trait_id')
            ->sourceMigration('Trait');
        $this->addFieldMapping('field_tqv_mean', 'mean');
        $this->addFieldMapping('field_tqv_sd', 'standard_deviation');
        $this->addFieldMapping('field_tqv_se', 'standard_error');
    }

    /**
     * Make sure there is value for the title destination field
     * and that the length of the string does not exceed 255
     * @param  [array] $current_row [The current row to be commited into the drupal database]
     * @return [boolean]              [Response to either to continue with adding the row or not]
     */
    public function prepareRow($current_row) {
        if(strlen($current_row->size) > 255){
            $current_row->size = substr($current_row->size, 0, 255);
        }
        if(!$current_row->size){
            $current_row->size = "Unspecified-" . time();
        }
        return TRUE;
    }

}
