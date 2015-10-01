<?php

/**
 * The CountryMigration uses the mi_term_countries table as source and
 * creates Drupal nodes of type 'Country' as destination.
 */

class CountryMigration extends DagrisMigration {
    public function __construct() {
        // call parent constructor
        parent::__construct();

        // add a description
        $this->description = t('Country migration');

        // add dependencies
        $this->dependencies = array('Region');

        // define query
        $query = Database::getConnection('default', 'dagris_migration')
            ->select('mi_taxonomy', 'ct')
            ->fields('ct', array(
                'id',
                'region_id',
                'name',
                'code',
                'iso3_code',
                'iso_number'
            ))
            ->condition('category', 'country');

        // orderBy('style_parent', 'ASC'); for those with self relationships

        $this->source = new MigrateSourceSQL($query);
        $this->destination = new MigrateDestinationTerm('country');
        $this->map = new MigrateSQLMap($this->machineName, array(
                'id' => array(
                    'type' => 'int',
                    'unsigned' => TRUE,
                    'not null' => TRUE,
                )
            ), MigrateDestinationTerm::getKeySchema()
        );

        $this->addFieldMapping('name', 'name');
        $this->addFieldMapping('field_ref_ct_region', 'region_id')
            ->sourceMigration('Region');
        $this->addFieldMapping('field_ct_code', 'code');
        $this->addFieldMapping('field_ct_iso3_code', 'iso3_code');
        $this->addFieldMapping('field_ct_iso_number', 'iso_number');
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
