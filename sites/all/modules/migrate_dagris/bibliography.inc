<?php

/**
 * Basic abstract intermediate class
 */
abstract class DagrisMigration extends DynamicMigration {
    public $basicFormat;

    public function __construct() {
        // parent constructor is called first
        parent::__construct(MigrateGroup::getInstance('dagris'));

        // set migration team members for the UI
        $this->team = array(
            new MigrateTeamMember('Tsegaselassie Tadesse', 'tsegaselassi@gmail.com', t('DAGRIS consultant'))
        );

        //$this->issuePattern = 'http://drupal.org/node/:id:';
        Database::addConnectionInfo('dagris_migration', 'default', array(
            'driver' => 'mysql',
            'database' => 'dagris_migration',
            'username' => 'root',
            'password' => 'root',
            'host' => 'localhost',
            'prefix' => '',
        ));

    }

}

/**
 * The BibliographyMigration uses the mi_node_bibliograpies table as source and
 * creates Drupal nodes of type 'Bibliogrpahy' as destination.
 */
class BibliographyMigration extends DagrisMigration {

    public function __construct() {
        // call parent constructor
        parent::__construct();

        // add a description
        $this->description = t('Bibliography migration');

        // define query
        $query = Database::getConnection('default', 'dagris_migration')
            ->select('mi_node_bibliographies', 'bi')
            ->fields('bi', array(
                'id',
                'control',
                'origin',
                'database_mfn',
                'sources',
                'ilri_pub_category',
                'bar_code_document_id',
                'author',
                'author_variant',
                'first_author_address',
                'corporate_author',
                'title',
                'subtitle',
                'parallel_titles',
                'title_in_english',
                'author_source',
                'corporate_source',
                'title_source',
                'series',
                'series_title_other',
                'volume_part_number',
                'issn',
                'languages_text',
                'languages_summary',
                'publisher',
                'place',
                'publication_year',
                'physical_description',
                'collation_notes',
                'edition',
                'isbn',
                'conference_name',
                'conference_place',
                'conference_date',
                'thesis',
                'patent_country',
                'subject_code',
                'record_type_form_doc',
                'descriptors',
                'proposed_descriptors',
                'cabi_descriptors',
                'abstract',
                'notes',
                'url'
            ));

        $this->source = new MigrateSourceSQL($query);
        $this->destination = new MigrateDestinationNode('bibliography');
        $this->map = new MigrateSQLMap($this->machineName, array(
                'id' => array(
                    'type' => 'int',
                    'unsigned' => TRUE,
                    'not null' => TRUE
                )
            ), MigrateDestinationNode::getKeySchema()
        );
        $this->addFieldMapping('title', 'title');
        $this->addFieldMapping('field_control', 'control');
        $this->addFieldMapping('field_origin', 'origin');
        $this->addFieldMapping('field_database_mfn', 'database_mfn');
        $this->addFieldMapping('field_sources', 'sources');
        $this->addFieldMapping('field_ilri_pub_category', 'ilri_pub_category');
        $this->addFieldMapping('field_bar_code_document_id', 'bar_code_document_id');
        $this->addFieldMapping('field_author', 'author');
        $this->addFieldMapping('field_author_variant', 'author_variant');
        $this->addFieldMapping('field_first_author_address', 'first_author_address');
        $this->addFieldMapping('field_corporate_author', 'corporate_author');
        $this->addFieldMapping('field_subtitle', 'subtitle');
        $this->addFieldMapping('field_parallel_titles', 'parallel_titles');
        $this->addFieldMapping('field_title_in_english', 'title_in_english');
        $this->addFieldMapping('field_author_source', 'author_source');
        $this->addFieldMapping('field_corporate_source', 'corporate_source');
        $this->addFieldMapping('field_title_source', 'title_source');
        $this->addFieldMapping('field_series', 'series');
        $this->addFieldMapping('field_series_title_other', 'series_title_other');
        $this->addFieldMapping('field_volume_part_number', 'volume_part_number');
        $this->addFieldMapping('field_issn', 'issn');
        $this->addFieldMapping('field_languages_text', 'languages_text');
        $this->addFieldMapping('field_languages_summary', 'languages_summary');
        $this->addFieldMapping('field_publisher', 'publisher');
        $this->addFieldMapping('field_place', 'place');
        $this->addFieldMapping('field_publication_year', 'publication_year');
        $this->addFieldMapping('field_physical_description', 'physical_description');
        $this->addFieldMapping('field_collation_notes', 'collation_notes');
        $this->addFieldMapping('field_edition', 'edition');
        $this->addFieldMapping('field_isbn', 'isbn');
        $this->addFieldMapping('field_conference_name', 'conference_name');
        $this->addFieldMapping('field_conference_place', 'conference_place');
        $this->addFieldMapping('field_conference_date', 'conference_date');
        $this->addFieldMapping('field_thesis', 'thesis');
        $this->addFieldMapping('field_patent_country', 'patent_country');
        $this->addFieldMapping('field_subject_code', 'subject_code');
        $this->addFieldMapping('field_record_type_from_document', 'record_type_form_doc');
        $this->addFieldMapping('field_descriptors', 'descriptors');
        $this->addFieldMapping('field_proposed_descriptors', 'proposed_descriptors');
        $this->addFieldMapping('field_cabi_descriptors', 'cabi_descriptors');
        $this->addFieldMapping('field_abstract', 'abstract');
        $this->addFieldMapping('field_notes', 'notes');
        $this->addFieldMapping('field_url', 'url');
    }

    /**
     * Make sure there is value for the title destination field
     * and that the length of the string does not exceed 255
     * @param  [array] $current_row [The current row to be commited into the drupal database]
     * @return [boolean]              [Response to either to continue with adding the row or not]
     */
    public function prepareRow($current_row) {
        if(strlen($current_row->title) > 255){
            $current_row->title = substr($current_row->title, 0, 255);
        }
        if(!$current_row->title){
            $current_row->title = "Unspecified-" . time();
        }
        return TRUE;
    }

}
