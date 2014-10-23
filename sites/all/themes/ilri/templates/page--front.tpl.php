<?php
/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * The doctype, html, head and body tags are not in this template. Instead they
 * can be found in the html.tpl.php template in this directory.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['highlighted']: Items for the highlighted content region.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['header']: Items for the header region.
 * - $page['footer']: Items for the footer region.
 *
 * @see bootstrap_preprocess_page()
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see bootstrap_process_page()
 * @see template_process()
 * @see html.tpl.php
 *
 * @ingroup themeable
 */
?>

<header id="navbar" role="banner" class="front-page-header <?php print $navbar_classes; ?>">
  <div class="container">
    <div class="navbar-header">
      <?php if ($logo): ?>
        <a class="logo navbar-btn pull-left" href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>">
          <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
        </a>
      <?php endif; ?>

      <?php if (!empty($site_name)): ?>
        <a class="name navbar-brand" href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>"><?php print $site_name; ?></a>
      <?php endif; ?>

      <!-- .btn-navbar is used as the toggle for collapsed navbar content -->
      <button type="button" class="navbar-toggle" data-toggle="collapse" data-target=".navbar-collapse">
        <span class="sr-only">Toggle navigation</span>
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
      </button>
    </div>

    <?php if (!empty($primary_nav) || !empty($secondary_nav) || !empty($page['navigation'])): ?>
      <div class="navbar-collapse collapse">
        <nav role="navigation">
          <?php if (!empty($primary_nav)): ?>
            <?php print render($primary_nav); ?>
          <?php endif; ?>
          <?php if (!empty($secondary_nav)): ?>
            <?php print render($secondary_nav); ?>
          <?php endif; ?>
          <?php if (!empty($page['navigation'])): ?>
            <div class="navbar-form navbar-right">
              <?php print render($page['navigation']); ?>
            </div>
          <?php endif; ?>
        </nav>
      </div>
    <?php endif; ?>
  </div>
</header>

<section id="slide-1" class="parallax">
  <div class="bcg"
  data-center="background-position: 50% 0px;"
  data-top-bottom="background-position: 50% -100px;"
  data-anchor-target="#slide-1">
  <div class="hsContainer">
    <div class="hsContent"
    data-top-top="opacity: 1; left: 0;"
    data--75-top-top="opacity: 0; left: -50%;"
    data-anchor-target="#slide-1 h1">
    <?php print render($page['parallax_section_1']); ?>
  </div>
</div>
</div>
</section>

<section id="slide-2" class="parallax">
  <div class="bcg"
  data-center="background-position: 50% 0px;"
  data-top-bottom="background-position: 50% -100px;"
  data-anchor-target="#slide-2">
  <div class="hsContainer"
       data-center="background-color:rgba(0,0,0,0.6)"
       data-bottom-top="background-color:rgba(0,0,0,0.0)">
    <div class="hsContent">
    <?php print render($page['parallax_section_2']); ?>
    <div class="row">
      <div class="col-md-4 main entities"
           data-bottom-top="left: -600px;"
           data-top="left: 0px;"
           data--200-top="left: 0px;"
           data-200-bottom="left: 0px;"
           data-top-bottom="left: -600px;"
           data-anchor-target="#slide-2"
      >
        <a id="species" href="#" class="active" data-show="#species-detail">
          Species
        </a>
        <a id="breeds" href="#" data-show="#breeds-detail">
          Breeds
        </a>
        <a id="breed-countries" href="#" data-show="#countries-detail">
            Countries
        </a>
        <a id="breed-images" href="#" data-show="#images-detail">
          Images
        </a>
        <a id="breed-web-links" href="#" data-show="#web-links-detail">
          Web Links
        </a>
        <a id="breed-triats" href="#" data-show="#traits-detail">
          Traits
        </a>
      </div>
      <div class="col-md-8 details"
           data-bottom-top="left: 600px;"
           data-top="left: 0px;"
           data--200-top="left: 0px;"
           data-200-bottom="left: 0px;"
           data-top-bottom="left: 600px;"
           data-anchor-target="#slide-2">
        <div id="species-detail" href="#" class="active">
          <h2>Species</h2>
          <p>
            General categories of domestic animals in <em>DAGRIS</em>. There are 8 such categories: Buffalo,
Cattle, Chickens, Dromedary Camels, Goats, Pigs, Sheep and Yaks.
          </p>
          <ul id="species-list" class='clearfix'>
            <li><img src="sites/all/themes/ilri/images/species_buffalo.png" alt="Buffalo"/></li>
            <li><img src="sites/all/themes/ilri/images/species_cattle.png" alt="Cattle"/></li>
            <li><img src="sites/all/themes/ilri/images/species_chicken.png" alt="Chicken"/></li>
            <li><img src="sites/all/themes/ilri/images/species_dormedary_camels.png" alt="Dormedary Camels"/></li>
            <li><img src="sites/all/themes/ilri/images/species_goats.png" alt="Goats"/></li>
            <li><img src="sites/all/themes/ilri/images/species_pigs.png" alt="Pigs"/></li>
            <li><img src="sites/all/themes/ilri/images/species_sheep.png" alt="Sheep"/></li>
            <li><img src="sites/all/themes/ilri/images/species_yaks.png" alt="Yaks"/></li>
          </ul>
        </div>
        <div id="breeds-detail">
          <h2>Breeds</h2>
          <p>
            The main focus of the DAGRIS system. A Breed describes an animal of a particular species, found in a specific country; exhibiting defined traits.
          </p>
        </div>
        <div id="countries-detail">
          <h2>Countries</h2>
          <p>
            The countries in which breeds are found. The are specfically 17 countries in Africa which are the focus of the DAGRIS project.
          </p>
          <p class="text-center">
            <img src="sites/all/themes/ilri/images/kafaci_members.png" alt="KAFACI Members"/>
          </p>
        </div>
        <div id="images-detail">
          <h2>Images</h2>
          <p>
            Image data of breeds managed using third party image hosting service, <a href="https://www.flickr.com/photos/ilri-dagris/">Flickr</a>.
          </p>
          <p class="text-center">
            <img src="sites/all/themes/ilri/images/flickr_dagris.png" alt="Flickr DAGRIS"/>
          </p>
        </div>
        <div id="web-links-detail">
          <h2>Web Links</h2>
          <p>
            External sources of information about a particular breed.
          </p>
          <p class="text-center">
            <img src="sites/all/themes/ilri/images/web_link_form.png" alt="Flickr DAGRIS"/>
          </p>
        </div>
        <div id="traits-detail">
          <h2>Traits</h2>
          <p>
            Characteristics of a given breed. Traits are mainly categorized into four groups:
          </p>
          <ul>
            <li>Genetic</li>
            <li>Physical</li>
            <li>Production</li>
            <li>Reproduction</li>
          </ul>
        </div>
      </div>
    </div>
  </div>
</div>
</div>
</section>

<section id="slide-3" class="parallax">
  <div class="bcg"
  data-center="background-position: 50% 0px;"
  data-top-bottom="background-position: 50% -100px;"
  data-anchor-target="#slide-3">
  <div class="hsContainer"
       data-center="background-color:rgba(0,0,0,0.6)"
       data-bottom-top="background-color:rgba(0,0,0,0.0)">
    <div class="hsContent"
    data-top-top="opacity: 1"
    data-top-bottom="opacity: 0"
    data-bottom-top="opacity: 0"
    data-anchor-target="#slide-3">
    <?php print render($page['parallax_section_3']); ?>
  </div>
</div>
</div>
</section>

<section id="slide-4" class="parallax">
  <div class="bcg"
  data-center="background-position: 50% 0px;"
  data-anchor-target="#slide-4">
  <div class="hsContainer"
       data-center="background-color:rgba(0,0,0,0.6)"
       data-bottom-top="background-color:rgba(0,0,0,0.0)">
    <div class="hsContent">
    <div class="row">
      <div class="col-md-4"
           data-bottom-top="left: -600px;"
           data-top="left: 0px;"
           data-anchor-target="#slide-4">
        <a href="https://ilri.org/users/skemp" class="circle-thumbnail" target="_blank">
          <img src="sites/default/files/placeholder.png" alt="Prof. Steve Kemp">
          <h3>Prof. Steve Kemp</h3>
          <p>
            Steve Kemp is a molecular geneticist particularly interested in the mechanisms of innate resistance to disease in livestock. He is a visiting scientist at ILRI and Professor of molecular genetics at the University of Liverpool, UK. Professor Kemp’s current research covers host genome diversity and adaptations to biotic and abiotic factors.
          </p>
        </a>
      </div>
      <div class="col-md-4"
           data-bottom-top="bottom: -600px;"
           data-top="bottom: 0px;"
           data-anchor-target="#slide-4">
        <a href="https://www.ilri.org/user/415" class="circle-thumbnail" target="_blank">
          <img src="sites/default/files/placeholder.png" alt="Dr. Tadelle Dessie">
          <h3>Dr. Tadelle Dessie</h3>
          <p>
            Tadelle Dessie has 20 years of research and development experience in various national and international research and development organizations. He has served as the group leader for Biotechnology Group based in ILRI-Ethiopia and is involved in the areas of knowledge management and capacity building. He is well versed with projects addressing research for development concentrating on understanding and improved utilization of animal resources to contribute for enhanced livelihoods of poor livestock keepers.
          </p>
        </a>
      </div>
      <div class="col-md-4"
           data-bottom-top="left: 600px;"
           data-top="left: 0px;"
           data-anchor-target="#slide-4">
        <a href="https://www.ilri.org/user/453" class="circle-thumbnail" target="_blank">
          <img src="sites/default/files/placeholder.png" alt="Mrs. Yetnayet Mamo">
          <h3>Yetnayet Mamo</h3>
          <p>
            Yetnayet Mamo Bishaw is an employee of the International Livestock Research Institute (ILRI) since September 1995 in Animal Genetic Resources Group (AnGR) first on temporary bases and then since June 2000 on permanent bases as Research Technologist in Addis Ababa, Ethiopia.
          </p>
        </a>
      </div>
    </div>
    <?php print render($page['parallax_section_4']); ?>
  </div>
</div>
</div>
</section>
