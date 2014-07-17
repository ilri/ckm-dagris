What is this?
-------------

This is a field type that will count the number of entityreferences to a
particular entity. This module is an adaptation of `Nodereference Count
<http://drupal.org/project/nodereference_count>`_ module porting the same
functionality to Entity References that is much more flexible in D7 because you
could reference any entity type and not only nodes.

How it works
------------

For a entity type that is referenced by other entities you can add an special
field of type entityreference_count that is an automatically calculated when
the referencing or referenced entity get inserted, updated or deleted. This
field has a configuration that allow to choice which fields from referencing
entity types you want to aggregate in the count. This way every time an entity
reference other entity this counter will be incremented and could be used to
display in the entity but also in as a field in a view.

Installation
------------

- Copy entityreference_count to your module directory and then enable on the
  admin modules page. 

- Be sure you have at least one entityreference field configured and then add a
  entityreference count field to a content type that is referenced by a
  entityreference. Check the boxes for the entityreference fields that should be
  counted. 

- You will need to re-save any existing entities or their referencing entities
  in order to update the count that will be empty for all the entities that
  exist previous the installation.

Credits
-------

- Thanks to all the hard work of Brendan Andersen (gilgabar) that created
  `Nodereference Count <http://drupal.org/project/nodereference_count>`_ module
  that introduced the approach to count references.  I did only an adaptation to
  make it work with Entity References that I believe is more powerful solution
  than Nodereferences in D7.

- The development of this module was sponsored by `BlueSpark Labs
  <http://www.bluesparklabs.com/>`_
