<?php

/**
 * The TraitTypeMigration uses the mi_node_trait_types table as source and
 * creates Drupal nodes of type 'TraitType' as destination.
 */
class TraitTypeMigration extends DagrisMigration {

    public function __construct() {
        // call parent constructor
        parent::__construct();

        // add a description
        $this->description = t('Trait Type migration');

        // add dependencies
        $this->dependencies = array('TraitCategory', 'SexGroup', 'TraitValueType');

        // define query
        $query = Database::getConnection('default', 'dagris_migration')
            ->select('mi_node_trait_types', 'tt')
            ->fields('tt', array(
                'id',
                'trait_category_id',
                'sex_group_id',
                'trait_value_type_id',
                'name',
                'description',
                'identifier_required',
                'identifier_name',
                'identify_what',
                'age_required',
                'use_in_summary'
            ));

        $this->source = new MigrateSourceSQL($query);
        $this->destination = new MigrateDestinationNode('trait_type');
        $this->map = new MigrateSQLMap($this->machineName, array(
                'id' => array(
                    'type' => 'int',
                    'unsigned' => TRUE,
                    'not null' => TRUE
                )
            ), MigrateDestinationNode::getKeySchema()
        );
        $this->addFieldMapping('title', 'name');
        $this->addFieldMapping('field_ref_tt_trait_category', 'trait_category_id')
            ->sourceMigration('TraitCategory');
        $this->addFieldMapping('field_ref_tt_sex_group', 'sex_group_id')
            ->sourceMigration('SexGroup');
        $this->addFieldMapping('field_ref_tt_trait_value_type', 'trait_value_type_id')
            ->sourceMigration('TraitValueType');
        $this->addFieldMapping('field_tt_description', 'description');
        $this->addFieldMapping('field_tt_identifier_required', 'identifier_required');
        $this->addFieldMapping('field_tt_identifier_name', 'identifier_name');
        $this->addFieldMapping('field_tt_identify_what', 'identify_what');
        $this->addFieldMapping('field_tt_age_required', 'age_required');
        $this->addFieldMapping('field_tt_use_in_summary', 'use_in_summary');
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
