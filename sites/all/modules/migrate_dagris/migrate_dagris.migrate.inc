<?php

/**
 * Implements hook_migrate_api().
 * Specifies we are using v2 of the migrate api
 *
 * @return int
 */
function migrate_dagris_migrate_api() {
    $api = array(
        'api' => 2,
        'migrations' => array(
            'Bibliography' => array('class_name' => 'BibliographyMigration'),
            'Breed' => array('class_name' => 'BreedMigration' ),
            'BreedCountry' => array('class_name' => 'BreedCountryMigration'),
            'BreedImage' => array('class_name' => 'BreedImageMigration'),
            'BreedWebLink' => array('class_name' => 'BreedWebLinkMigration'),
            'Contact' => array('class_name' => 'ContactMigration'),
            'Population' => array('class_name' => 'PopulationMigration'),
            'StudyLocation' => array('class_name' => 'StudyLocationMigration'),
            'TraitAge' => array('class_name' => 'TraitAgeMigration'),
            'TraitIdentifier' => array('class_name' => 'TraitIdentifierMigration'),
            'TraitQuantitativeValue' => array('class_name' => 'TraitQuantitativeValueMigration'),
            'TraitType' => array('class_name' => 'TraitTypeMigration'),
            'Trait' => array('class_name' => 'TraitMigration'),
            'BreedGroup' => array('class_name' => 'BreedGroupMigration'),
            'Country' => array('class_name' => 'CountryMigration'),
            'DocumentType' => array('class_name' => 'DocumentTypeMigration'),
            'ManagementCondition' => array('class_name' => 'ManagementConditionMigration'),
            'Region' => array('class_name' => 'RegionMigration'),
            'RiskStatus' => array('class_name' => 'RiskStatusMigration'),
            'SexGroup' => array('class_name' => 'SexGroupMigration'),
            'Sex' => array('class_name' => 'SexMigration'),
            'Species' => array('class_name' => 'SpeciesMigration'),
            'TraitCategory' => array('class_name' => 'TraitCategoryMigration'),
            'TraitValueType' => array('class_name' => 'TraitValueTypeMigration'),
        ),
    );
    return $api;
}
