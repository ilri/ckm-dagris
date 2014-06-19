<?php

/**
 * The BreedMigration uses the mi_node_breeds table as source and
 * creates Drupal nodes of type 'Breed' as destination.
 */
class BreedMigration extends DagrisMigration {

    public function __construct() {
        // call parent constructor
        parent::__construct();

        // add a description
        $this->description = t('Breed migration');

        // add dependencies
        $this->dependencies = array('BreedGroup');

        // define query
        $query = Database::getConnection('default', 'dagris_migration')
            ->select('mi_node_breeds', 'br')
            ->fields('br', array(
                'id',
                'group_id',
                'name_strain',
                'name_synonym',
                'subgroup_info',
                'origin',
                'habitat',
                'main_location',
                'special_characteristics'
            ));

        $this->source = new MigrateSourceSQL($query);
        $this->destination = new MigrateDestinationNode('breed');
        $this->map = new MigrateSQLMap($this->machineName, array(
                'id' => array(
                    'type' => 'int',
                    'unsigned' => TRUE,
                    'not null' => TRUE
                )
            ), MigrateDestinationNode::getKeySchema()
        );
        $this->addFieldMapping('title', 'name_strain');
        $this->addFieldMapping('field_ref_br_group', 'group_id')
            ->sourceMigration('BreedGroup');
        $this->addFieldMapping('field_synonyms', 'name_synonym');
        $this->addFieldMapping('field_subgroup', 'subgroup_info');
        $this->addFieldMapping('field_br_origin', 'origin');
        $this->addFieldMapping('field_br_habitat', 'habitat');
        $this->addFieldMapping('field_br_main_location', 'main_location');
        $this->addFieldMapping('field_special_characteristics', 'special_characteristics');
    }

    /**
     * Make sure there is value for the title destination field
     * and that the length of the string does not exceed 255
     * @param  [array] $current_row [The current row to be commited into the drupal database]
     * @return [boolean]              [Response to either to continue with adding the row or not]
     */
    public function prepareRow($current_row) {
        if(strlen($current_row->name_strain) > 255){
            $current_row->name_strain = substr($current_row->name_strain, 0, 255);
        }
        if(!$current_row->name_strain){
            $current_row->name_strain = "Unspecified-" . time();
        }
        return TRUE;
    }

}
