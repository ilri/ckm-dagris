(function($) {
  Drupal.d3.dagris_map = function(select, settings) {

    var data = [];
    for (var r = 0; r < settings.rows.length; r++) {
      var last_element = data.pop();
      if (!last_element) { // First element
        data.push({
          name: settings.rows[r][0],
          id: settings.rows[r][1] * 1,
          stats: [{
            species: settings.rows[r][2],
            breeds: settings.rows[r][3]
          }]
        });
      } else {
        if (last_element.id == settings.rows[r][1]) { // Entry for the same country
          last_element.stats.push({
            species: settings.rows[r][2],
            breeds: settings.rows[r][3]
          });
          data.push(last_element);
        } else { // Entry for a different country
          data.push(last_element);
          data.push({
            name: settings.rows[r][0],
            id: settings.rows[r][1],
            stats: [{
              species: settings.rows[r][2],
              breeds: settings.rows[r][3]
            }]
          });
        }
      }
    }

    var width = "100%",
      height = 500;

    var svg_container_id = "report-" + new Date().getTime();
    $("div.d3.dagris_map.d3-processed").append("<div id='" + svg_container_id + "'></div>");

    var projection = d3.geo.mercator()
      .center([12, 15])
      .scale(150);

    var svg = d3.select("#" + svg_container_id).append("svg")
      .attr("width", width)
      .attr("height", height);

  // console.log($("svg").width());

    var path = d3.geo.path()
      .projection(projection);

    var svg_width = $("svg").width(),
        map_g_width = $("svg g").width();

    projection.translate([(svg_width - map_g_width) / 2, height / 2]);

    var g = svg.append("g");

    queue()
      .defer(d3.json, "/sites/all/libraries/d3.dagris_map/world-110m.json")
      .defer(d3.tsv, "/sites/all/libraries/d3.dagris_map/world-country-names.tsv")
      .await(ready);

    function ready(error, world, names) {

      _.each(names, function(name) {
        var data_for_name = _.find(data, function(d) {
          return name.id == d.id;
        });
        if (data_for_name && data_for_name.stats) {
          _.each(data_for_name.stats, function(v) {
            name.stats_text = name.stats_text ? name.stats_text + "<strong>" + v.species + "</strong>:" + v.breeds + "<br>" : "<strong>" + v.species + "</strong>:" + v.breeds + "<br>";
          });
        }
      });

      // Get the geometries of the countries
      var geos = topojson.object(world, world.objects.countries).geometries;

      // Add name data to each geometry
      geos = geos.filter(function(d) {
          return names.some(function(n) {
            if (d.id == n.id) {
              d.stats_text = n.stats_text ? n.stats_text : "No Entries Yet!";
              return d.name = n.name;
            }
          });
        })
        .sort(function(a, b) {
          return a.name.localeCompare(b.name);
        });

      g.selectAll("path")
        .data(geos)
        .enter()
        .append("path")
        .attr("d", path)
        .attr("id", function(d) {
          return d.id;
        })
        .attr("class", "countries")
        .attr("name", function(d) {
          return d.name;
        })
        .attr("text", function(d) {
          return d.stats_text;
        });
    }

    // zoom and pan
    var zoom = d3.behavior.zoom()
      .on("zoom", function() {
        g.attr("transform", "translate(" +
          d3.event.translate.join(",") + ")scale(" + d3.event.scale + ")");
        g.selectAll("path")
          .attr("d", path.projection(projection));
      });

    svg.call(zoom);
  };

  var mouseX;
  var mouseY;
  $(document).mousemove(function(e) {
    mouseX = e.pageX;
    mouseY = e.pageY + 10;
  });

  $(document).delegate(".countries", "mouseover", function() {
    var country_name = $(this).attr("name");
    var stats_text = $(this).attr("text");
    $("body").append("<div id='map-tool-tip' class='popover top'><h3 class='popover-title'>" + country_name + "</h3><div class='popover-content'>" + stats_text + "</div></div>");
    $("#map-tool-tip").css({
      'top': mouseY,
      'left': mouseX
    }).fadeIn('slow');
  });

  $(document).delegate(".countries", "mouseleave", function() {
    $("#map-tool-tip").remove();
  });

})(jQuery);
