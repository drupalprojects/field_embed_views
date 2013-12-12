
Field Embed Views
-----------------
Provides a field type, to which any views can be attached with custom views settings.

Each field item is internally represented as an set of view settings.
Field allow to save View settings (exposed filters) in Drupal entity and
output that View with saved settings as entity field.
The placement of the View in the content can be reordered on the
"Field Display" administration page for that entity.

 Usage
 ------

  * Go to "Admin -> Modules" and enable module Field Embed Views.

  * Then go to "Admin -> Structure-> Views -> Add new view" to define new view
   or use already create view. Configure exposed filters that will be embed in
   entity form.

  * Add a field embed views to any entity, e.g. to a node. For that use the
   the usual "Manage fields" interface provided by the "field ui" module of
   Drupal, e.g. "Admin -> Structure-> Content types -> Article -> Manage fields".
   In field instance settings select View and Display.

Restrictions
-------------

  * As of now, the field embed views save only exposed filter settings of views.