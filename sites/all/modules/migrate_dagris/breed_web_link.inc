<?php

/**
 * The BreedWebLinkMigration uses the mi_node_breed_web_links table as source and
 * creates Drupal nodes of type 'BreedWebLink' as destination.
 */
class BreedWebLinkMigration extends DagrisMigration {

    public function __construct() {
        // call parent constructor
        parent::__construct();

        // add a description
        $this->description = t('Breed Web Link migration');

        // add dependencies
        $this->dependencies = array('Breed');

        // define query
        $query = Database::getConnection('default', 'dagris_migration')
            ->select('mi_node_breed_web_links', 'bwl')
            ->fields('bwl', array(
                'id',
                'breed_id',
                'url',
                'description',
                'summary'
            ));

        $this->source = new MigrateSourceSQL($query);
        $this->destination = new MigrateDestinationNode('breed_weblink');
        $this->map = new MigrateSQLMap($this->machineName, array(
                'id' => array(
                    'type' => 'int',
                    'unsigned' => TRUE,
                    'not null' => TRUE
                )
            ), MigrateDestinationNode::getKeySchema()
        );
        $this->addFieldMapping('title', 'url');
        $this->addFieldMapping('field_ref_bw_breed', 'breed_id')
            ->sourceMigration('Breed');
        $this->addFieldMapping('field_bw_description', 'description');
        $this->addFieldMapping('field_bw_summary', 'summary');
    }

    /**
     * Make sure there is value for the title destination field
     * and that the length of the string does not exceed 255
     * @param  [array] $current_row [The current row to be commited into the drupal database]
     * @return [boolean]              [Response to either to continue with adding the row or not]
     */
    public function prepareRow($current_row) {
        if(strlen($current_row->url) > 255){
            $current_row->url = substr($current_row->url, 0, 255);
        }
        if(!$current_row->url){
            $current_row->url = "Unspecified-" . time();
        }
        return TRUE;
    }

}
