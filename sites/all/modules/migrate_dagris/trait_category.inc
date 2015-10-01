<?php

/**
 * The Trait Category Migration uses the mi_term_trait_category table as source and
 * creates Drupal nodes of type 'TraitCategory' as destination.
 */

class TraitCategoryMigration extends DagrisMigration {
    public function __construct() {
        // call parent constructor
        parent::__construct();

        // add a description
        $this->description = t('Trait Category migration');

        // define query
        $query = Database::getConnection('default', 'dagris_migration')
            ->select('mi_taxonomy', 'tc')
            ->fields('tc', array(
                'id',
                'name',
            ))
            ->condition('category', 'trait_category');

        $this->source = new MigrateSourceSQL($query);
        $this->destination = new MigrateDestinationTerm('trait_category');
        $this->map = new MigrateSQLMap($this->machineName, array(
                'id' => array(
                    'type' => 'int',
                    'unsigned' => TRUE,
                    'not null' => TRUE,
                )
            ), MigrateDestinationTerm::getKeySchema()
        );

        $this->addFieldMapping('name', 'name');
    }

    /**
     * Make sure there is value for the title destination field
     * and that the length of the string does not exceed 255
     * @param  [array] $current_row [The current row to be commited into the drupal database]
     * @return [boolean]              [Response to either to continue with adding the row or not]
     */
    public function prepareRow($current_row) {
        if(strlen($current_row->name) > 255){
            $current_row->name = substr($current_row->name, 0, 255);
        }
        if(!$current_row->name){
            $current_row->name = "Unspecified-" . time();
        }
        return TRUE;
    }
}
