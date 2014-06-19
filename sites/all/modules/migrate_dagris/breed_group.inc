<?php

/**
 * The Breed GroupMigration uses the mi_term_breed_groups table as source and
 * creates Drupal nodes of type 'BreedGroup' as destination.
 */

class BreedGroupMigration extends DagrisMigration {
    public function __construct() {
        // call parent constructor
        parent::__construct();

        // add a description
        $this->description = t('Breed Group migration');

        // add dependencies
        $this->dependencies = array('Species');

        // define query
        $query = Database::getConnection('default', 'dagris_migration')
            ->select('mi_taxonomy', 'bg')
            ->fields('bg', array(
                'id',
                'species_id',
                'name',
                'origin'
            ))
            ->condition('category', 'breed_group');

        $this->source = new MigrateSourceSQL($query);
        $this->destination = new MigrateDestinationTerm('breed_group');
        $this->map = new MigrateSQLMap($this->machineName, array(
                'id' => array(
                    'type' => 'int',
                    'unsigned' => TRUE,
                    'not null' => TRUE,
                )
            ), MigrateDestinationTerm::getKeySchema()
        );

        $this->addFieldMapping('name', 'name');
        $this->addFieldMapping('field_ref_bg_species', 'species_id')
             ->sourceMigration('Species');
        $this->addFieldMapping('field_bg_origin', 'origin');
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
