<?php

/**
 * The BreedCountryMigration uses the mi_node_breed_countries table as source and
 * creates Drupal nodes of type 'BreedCountry' as destination.
 */
class BreedCountryMigration extends DagrisMigration {

    public function __construct() {
        // call parent constructor
        parent::__construct();

        // add a description
        $this->description = t('Breed Country migration');

        // add dependencies
        $this->dependencies = array('Breed', 'Country');

        // define query
        $query = Database::getConnection('default', 'dagris_migration')
            ->select('mi_node_breed_countries', 'bc')
            ->fields('bc', array(
                'id',
                'breed_id',
                'country_id',
                'local_name',
                'present_use',
                'main_location',
                'risk_cause',
                'habitat',
                'rain_fall',
                'temperature',
                'relative_humidity',
                'vegitation',
                'altitude',
                'latitude',
                'longitude',
                'comment',
            ));

        $this->source = new MigrateSourceSQL($query);
        $this->destination = new MigrateDestinationNode('breed_country');
        $this->map = new MigrateSQLMap($this->machineName, array(
                'id' => array(
                    'type' => 'int',
                    'unsigned' => TRUE,
                    'not null' => TRUE
                )
            ), MigrateDestinationNode::getKeySchema()
        );
        $this->addFieldMapping('title', 'local_name');
        $this->addFieldMapping('field_ref_breed', 'breed_id')
            ->sourceMigration('Breed');
        $this->addFieldMapping('field_ref_bc_country', 'country_id')
            ->sourceMigration('Country');
        $this->addFieldMapping('field_present_use', 'present_use');
        $this->addFieldMapping('field_bc_main_location', 'main_location');
        $this->addFieldMapping('field_risk_cause', 'risk_cause');
        $this->addFieldMapping('field_habitat', 'habitat');
        $this->addFieldMapping('field_rainfall', 'rain_fall');
        $this->addFieldMapping('field_temperature', 'temperature');
        $this->addFieldMapping('field_relative_humidity', 'relative_humidity');
        $this->addFieldMapping('field_vegetation', 'vegitation');
        $this->addFieldMapping('field_altitude', 'altitude');
        $this->addFieldMapping('field_latitude', 'latitude');
        $this->addFieldMapping('field_longitude', 'longitude');
        $this->addFieldMapping('field_bc_comment', 'comment');
    }

    /**
     * Make sure there is value for the title destination field
     * and that the length of the string does not exceed 255
     * @param  [array] $current_row [The current row to be commited into the drupal database]
     * @return [boolean]              [Response to either to continue with adding the row or not]
     */
    public function prepareRow($current_row) {
        if(strlen($current_row->local_name) > 255){
            $current_row->local_name = substr($current_row->local_name, 0, 255);
        }
        if(!$current_row->local_name){
            $current_row->local_name = "Unspecified-" . time();
        }
        return TRUE;
    }
}
