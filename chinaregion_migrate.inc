<?php
/**
 * @file
 * using the Migrate module to import taxonomy
 */

class ChinaRegionMigration extends Migration {
  public function __construct() {
    parent::__construct();

    $this->description = t('Migrate china region from the source database to taxonomy terms');

    $this->map = new MigrateSQLMap($this->machineName,
                 array(
                   'aid' => array(
                     'type' => 'int',
                     'not null' => TRUE,
                     'description' => 'area id',
                   )
                 ),
                 MigrateDestinationTerm::getKeySchema()
    );

    $query = db_select('chinaregion_migrate_area', 'cma');
    //    $query->leftJoin('chinaregion_migrate_area', 'parent', 'parent.aid=cma.parent_id');
    //    $query->addField('parent', 'name', 'parent_name');
    $query->fields('cma', array('aid', 'code', 'name', 'level', 'parent_id'))
      ->orderBy('cma.level', 'ASC');

    // Create a MigrateSource object, which manages retrieving the input data.
    $this->source = new MigrateSourceSQL($query);

    // Set up our destination - terms in the migrate_example_beer_styles vocabulary
    $this->destination = new MigrateDestinationTerm('chinaregion_migrate_region');

    // Assign mappings TO destination fields FROM source fields.
    $this->addFieldMapping('name', 'name');
    $this->addFieldMapping('chinaregion_migrate_code', 'code');
    $this->addFieldMapping('parent', 'parent_id')
      ->sourceMigration($this->getMachineName());
    $this->addFieldMapping('chinaregion_migrate_level', 'level');

    $this->addFieldMapping('format')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping('weight')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping('parent_name')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping('description')
         ->issueGroup(t('DNM'));

    $this->addFieldMapping('chinaregion_migrate_code:language')
      ->issueGroup(t('DNM'));

    if (module_exists('path')) {
      $this->addFieldMapping('path')
           ->issueGroup(t('DNM'));
    }
  }
}

