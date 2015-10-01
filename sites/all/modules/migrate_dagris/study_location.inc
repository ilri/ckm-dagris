<?php

/**
 * The StudyLocationMigration uses the mi_node_StudyLocations table as source and
 * creates Drupal nodes of type 'StudyLocation' as destination.
 */
class StudyLocationMigration extends DagrisMigration {

    public function __construct() {
        // call parent constructor
        parent::__construct();

        // add a description
        $this->description = t('Study Location migration');

        // add dependencies
        $this->dependencies = array('Country', 'ManagementCondition');

        // define query
        $query = Database::getConnection('default', 'dagris_migration')
            ->select('mi_node_study_locations', 'sl')
            ->fields('sl', array(
                'id',
                'country_id',
                'management_condition_id',
                'code',
                'name',
                'longitude',
                'latitude',
                'altitude',
                'temperature',
                'rainfall',
                'elivation',
                'vegitation',
                'soil_type',
                'comment'
            ));

        $this->source = new MigrateSourceSQL($query);
        $this->destination = new MigrateDestinationNode('study_location');
        $this->map = new MigrateSQLMap($this->machineName, array(
                'id' => array(
                    'type' => 'int',
                    'unsigned' => TRUE,
                    'not null' => TRUE
                )
            ), MigrateDestinationNode::getKeySchema()
        );
        $this->addFieldMapping('title', 'name');
        $this->addFieldMapping('field_ref_sl_country', 'country_id')
            ->sourceMigration('Country');
        $this->addFieldMapping('field_ref_sl_mc', 'management_condition_id')
            ->sourceMigration('ManagementCondition');
        $this->addFieldMapping('field_sl_code', 'code');
        $this->addFieldMapping('field_sl_longitude', 'longitude');
        $this->addFieldMapping('field_sl_latitude', 'latitude');
        $this->addFieldMapping('field_sl_altitude', 'altitude');
        $this->addFieldMapping('field_sl_temperature', 'temperature');
        $this->addFieldMapping('field_sl_rainfall', 'rainfall');
        $this->addFieldMapping('field_sl_elevation', 'elivation');
        $this->addFieldMapping('field_sl_vegetation', 'vegitation');
        $this->addFieldMapping('field_sl_soil_type', 'soil_type');
        $this->addFieldMapping('field_sl_comment', 'comment');
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
