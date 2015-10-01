<?php

/**
 * The BreedImageMigration uses the mi_node_breeds table as source and
 * creates Drupal nodes of type 'BreedImage' as destination.
 */
class BreedImageMigration extends DagrisMigration {

    public function __construct() {
        // call parent constructor
        parent::__construct();

        // add a description
        $this->description = t('Breed Image migration');

        // add dependencies
        $this->dependencies = array('Breed');

        // define query
        $query = Database::getConnection('default', 'dagris_migration')
            ->select('mi_node_breed_images', 'bi')
            ->fields('bi', array(
                'id',
                'breed_id',
                'caption',
                'url',
                'description',
                'institution',
                'copyright',
                'date'
            ));

        $this->source = new MigrateSourceSQL($query);
        $this->destination = new MigrateDestinationNode('breed_image');
        $this->map = new MigrateSQLMap($this->machineName, array(
                'id' => array(
                    'type' => 'int',
                    'unsigned' => TRUE,
                    'not null' => TRUE
                )
            ), MigrateDestinationNode::getKeySchema()
        );
        $this->addFieldMapping('title', 'caption');
        $this->addFieldMapping('field_ref_img_breed', 'breed_id')
            ->sourceMigration('Breed');
        $this->addFieldMapping('field_img_url', 'url');
        $this->addFieldMapping('field_img_description', 'description');
        $this->addFieldMapping('field_img_institution', 'institution');
        $this->addFieldMapping('field_img_copyright', 'copyright');
        $this->addFieldMapping('field_img_date', 'date');
    }

    /**
     * Make sure there is value for the title destination field
     * and that the length of the string does not exceed 255
     * @param  [array] $current_row [The current row to be commited into the drupal database]
     * @return [boolean]              [Response to either to continue with adding the row or not]
     */
    public function prepareRow($current_row) {
        if(strlen($current_row->caption) > 255){
            $current_row->caption = substr($current_row->caption, 0, 255);
        }
        if(!$current_row->caption){
            $current_row->caption = "Unspecified-" . time();
        }
        return TRUE;
    }

}
