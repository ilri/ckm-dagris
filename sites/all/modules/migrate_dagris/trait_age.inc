<?php

/**
 * The TraitAgeMigration uses the mi_node_trait_ages table as source and
 * creates Drupal nodes of type 'TraitAge' as destination.
 */
class TraitAgeMigration extends DagrisMigration {

    public function __construct() {
        // call parent constructor
        parent::__construct();

        // add a description
        $this->description = t('Trait Age migration');

        // add dependencies
        $this->dependencies = array('Trait');

        // define query
        $query = Database::getConnection('default', 'dagris_migration')
            ->select('mi_node_trait_ages', 'ta')
            ->fields('ta', array(
                'id',
                'trait_id',
                'value'
            ));

        $this->source = new MigrateSourceSQL($query);
        $this->destination = new MigrateDestinationNode('trait_age');
        $this->map = new MigrateSQLMap($this->machineName, array(
                'id' => array(
                    'type' => 'int',
                    'unsigned' => TRUE,
                    'not null' => TRUE
                )
            ), MigrateDestinationNode::getKeySchema()
        );
        $this->addFieldMapping('title', 'value');
        $this->addFieldMapping('field_ref_ta_trait', 'trait_id')
            ->sourceMigration('Trait');
    }

    /**
     * Make sure there is value for the title destination field
     * and that the length of the string does not exceed 255
     * @param  [array] $current_row [The current row to be commited into the drupal database]
     * @return [boolean]              [Response to either to continue with adding the row or not]
     */
    public function prepareRow($current_row) {
        if(strlen($current_row->value) > 255){
            $current_row->value = substr($current_row->value, 0, 255);
        }
        if(!$current_row->value){
            $current_row->value = "Unspecified-" . time();
        }
        return TRUE;
    }

}
