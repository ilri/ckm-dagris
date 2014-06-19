<?php

/**
 * The BreedMigration uses the mi_node_breeds table as source and
 * creates Drupal nodes of type 'Breed' as destination.
 */
class PopulationMigration extends DagrisMigration {

    public function __construct() {
        // call parent constructor
        parent::__construct();

        // add a description
        $this->description = t('Population migration');

        // add dependencies
        $this->dependencies = array('BreedCountry', 'Bibliography');

        // define query
        $query = Database::getConnection('default', 'dagris_migration')
            ->select('mi_node_populations', 'bp')
            ->fields('bp', array(
                'id',
                'breed_country_id',
                'bibliography_id',
                'size',
                'census_year',
                'report_year',
                'female_number',
                'male_number',
                'PDAINo',
                'female_trend',
                'comment',
                'published'
            ));

        $this->source = new MigrateSourceSQL($query);
        $this->destination = new MigrateDestinationNode('breed_population');
        $this->map = new MigrateSQLMap($this->machineName, array(
                'id' => array(
                    'type' => 'int',
                    'unsigned' => TRUE,
                    'not null' => TRUE
                )
            ), MigrateDestinationNode::getKeySchema()
        );
        $this->addFieldMapping('title', 'size');
        $this->addFieldMapping('field_ref_bp_breed_country', 'breed_country_id')
            ->sourceMigration('BreedCountry');
        $this->addFieldMapping('field_ref_bp_bibliography', 'bibliography_id')
            ->sourceMigration('Bibliography');
        $this->addFieldMapping('field_census_year', 'census_year');
        $this->addFieldMapping('field_report_year', 'report_year');
        $this->addFieldMapping('field_number_of_females', 'female_number');
        $this->addFieldMapping('field_number_of_males', 'male_number');
        $this->addFieldMapping('field_number_in_ai', 'PDAINo');
        $this->addFieldMapping('field_trend_of_females', 'female_trend');
        $this->addFieldMapping('field_bp_published', 'published');
        $this->addFieldMapping('field_bp_comment', 'comment');
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
