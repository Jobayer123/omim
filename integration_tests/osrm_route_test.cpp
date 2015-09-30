#include "testing/testing.hpp"

#include "integration_tests/routing_test_tools.hpp"

#include "../indexer/mercator.hpp"

using namespace routing;

namespace
{
  // Restrictions tests. Check restrictions generation, if there are any errors.
  UNIT_TEST(RestrictionTestNeatBaumanAndTTK)
  {
    integration::CalculateRouteAndTestRouteLength(
          integration::GetOsrmComponents(),
          MercatorBounds::FromLatLon(55.77399, 37.68468), {0., 0.},
          MercatorBounds::FromLatLon(55.77198, 37.68782), 900.);
  }

  UNIT_TEST(RestrictionTestNearMetroShodnenskaya)
  {
    integration::CalculateRouteAndTestRouteLength(
          integration::GetOsrmComponents(),
          MercatorBounds::FromLatLon(55.85043, 37.43824), {0., 0.},
          MercatorBounds::FromLatLon(55.85191, 37.43910), 510.
          );
  }

  // Strange asserts near Cupertino test
  UNIT_TEST(CaliforniaCupertinoFindPhantomAssertTest)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetOsrmComponents(), MercatorBounds::FromLatLon(37.33409, -122.03458), {0., 0.},
        MercatorBounds::FromLatLon(37.33498, -122.03575), 1438.);
  }

  // ASSERT on pedestrian edges
  UNIT_TEST(RussiaAssertHighwayClassOnPedestrianRouteInOSRM)
  {
    integration::CalculateRouteAndTestRouteLength(
          integration::GetOsrmComponents(),
          MercatorBounds::FromLatLon(55.77787, 37.70405), {0., 0.},
          MercatorBounds::FromLatLon(55.77682, 37.70391), 185.
          );
  }

  // Geometry unpacking test.
  UNIT_TEST(RussiaFerryToCrimeaLoadCrossGeometryTest)
  {
    // Forward
    TRouteResult route = integration::CalculateRoute(
                         integration::GetOsrmComponents(), MercatorBounds::FromLatLon(45.34123, 36.67679),
                         {0., 0.}, MercatorBounds::FromLatLon(45.36479, 36.62194));
    TEST_EQUAL(route.second, IRouter::NoError, ());
    TEST_GREATER(route.first->GetPoly().GetSize(), 50, ());
    // And backward case
    route = integration::CalculateRoute(
            integration::GetOsrmComponents(), MercatorBounds::FromLatLon(45.36479, 36.62194), {0., 0.},
            MercatorBounds::FromLatLon(45.34123, 36.67679));
    TEST_EQUAL(route.second, IRouter::NoError, ());
    TEST_GREATER(route.first->GetPoly().GetSize(), 50, ());
  }

  UNIT_TEST(PriceIslandLoadCrossGeometryTest)
  {
    // Forward
    TRouteResult route = integration::CalculateRoute(
                         integration::GetOsrmComponents(), MercatorBounds::FromLatLon(46.16255,-63.81643),
                         {0., 0.}, MercatorBounds::FromLatLon(46.25401, -63.70213));
    TEST_EQUAL(route.second, IRouter::NoError, ());
    TEST_GREATER(route.first->GetPoly().GetSize(), 29, ());
    // And backward case
    route = integration::CalculateRoute(
            integration::GetOsrmComponents(), MercatorBounds::FromLatLon(46.25401, -63.70213), {0., 0.},
            MercatorBounds::FromLatLon(46.16255,-63.81643));
    TEST_EQUAL(route.second, IRouter::NoError, ());
    TEST_GREATER(route.first->GetPoly().GetSize(), 29, ());
  }

  // Cross mwm tests.
  UNIT_TEST(RussiaMoscowLeningradskiy39GerPanfilovtsev22RouteTest)
  {
    integration::CalculateRouteAndTestRouteLength(integration::GetOsrmComponents(),
                                                  {37.53758809983519, 67.536162466434234}, {0., 0.},
                                                  {37.40993977728661, 67.644784047393685}, 14296.);
  }

  UNIT_TEST(RussiaMoscowGerPanfilovtsev22SolodchaPravdiRouteTest)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetOsrmComponents(), {37.409929478750627, 67.644798619710073}, {0., 0.},
        {39.836562407458047, 65.774372510437971}, 239426.);
  }

  // TODO OSRM offers a possible turn to a pedestrian road in this test. It's fixing right now.
  UNIT_TEST(UKRugbyStIvesRouteTest)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetOsrmComponents(), {-1.2653036222483705, 61.691304855049886}, {0., 0.},
        {-5.4799407508360218, 58.242809563579847}, 455902.);
  }

  UNIT_TEST(RussiaMoscowLenigradskiy39ItalySienaCenterRouteTest)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetOsrmComponents(), {37.537596024929826, 67.536160359657288}, {0., 0.},
        {11.327927635052676, 48.166256203616726}, 2870710.);
  }

  UNIT_TEST(RussiaMoscowFranceParisCenterRouteTest)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetOsrmComponents(),
        MercatorBounds::FromLatLon(55.75271, 37.62618), {0., 0.},
        MercatorBounds::FromLatLon(48.86123, 2.34129), 2840940.);
  }

// @TODO This test is failed to create a route for the time being with data from 12.09.2015.
// Now it's impossible to create a vehicle route from Paris to London.
// The assumed reason is some tags of the tunnel were changed and we stop working with
// the situation correctly.
// At the same time OSRM manages to create routes through the tunnel.
  UNIT_TEST(FranceParisCenternglandLondonCenterRouteTest)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetOsrmComponents(),
        MercatorBounds::FromLatLon(48.86123, 2.34129), {0., 0.},
        MercatorBounds::FromLatLon(51.49884, -0.10438), 0./* Some unknown value*/);
  }

  // Strange map edits in Africa borders. Routing not linked now.
  /*
  UNIT_TEST(RussiaMoscowLenigradskiy39RepublicOfSouthAfricaCapeTownCenterRouteTest)
  {
    //@todo put down a correct route length when router is fixed
    integration::CalculateRouteAndTestRouteLength(
        integration::GetOsrmComponents(), {37.53754, 67.53622}, {0., 0.},
        {18.54269, -36.09501}, 17873000.);
  }*/

  UNIT_TEST(MoroccoToSahrawiCrossMwmTest)
  {
    integration::CalculateRouteAndTestRouteLength(
        integration::GetOsrmComponents(), MercatorBounds::FromLatLon(27.15587, -13.23059), {0., 0.},
        MercatorBounds::FromLatLon(27.94049, -12.88800), 100864);
    integration::CalculateRouteAndTestRouteLength(
        integration::GetOsrmComponents(), MercatorBounds::FromLatLon(27.94049, -12.88800), {0., 0.},
        MercatorBounds::FromLatLon(27.15587, -13.23059), 100864);
  }

  UNIT_TEST(ArbatBaliCrimeanCrossMwmTest)
  {
    // Forward case.
    integration::CalculateRouteAndTestRouteLength(
        integration::GetOsrmComponents(), MercatorBounds::FromLatLon(45.90668,34.87221), {0., 0.},
        MercatorBounds::FromLatLon(45.35697, 35.36971), 75000.);
    // Backward case.
    integration::CalculateRouteAndTestRouteLength(
        integration::GetOsrmComponents(), MercatorBounds::FromLatLon(45.35697, 35.36971), {0., 0.},
        MercatorBounds::FromLatLon(45.90668,34.87221), 75000.);

  }

  UNIT_TEST(AlbaniaToMontenegroCrossTest)
  {
    // Road from Albania to Montenegro. Test turnaround finding at border (when start/stop OSRM
    // points are inside borders and one of segments has outside points).
    // Forward
    integration::CalculateRouteAndTestRouteLength(
        integration::GetOsrmComponents(), MercatorBounds::FromLatLon(42.01535, 19.40044), {0., 0.},
        MercatorBounds::FromLatLon(42.01201, 19.36286), 3674.);
    // And backward case
    integration::CalculateRouteAndTestRouteLength(
        integration::GetOsrmComponents(), MercatorBounds::FromLatLon(42.01201, 19.36286), {0., 0.},
        MercatorBounds::FromLatLon(42.01535, 19.40044), 3674.);
  }

  UNIT_TEST(CanadaBridgeCrossToEdwardIsland)
  {
    // Forward
    integration::CalculateRouteAndTestRouteLength(
        integration::GetOsrmComponents(), MercatorBounds::FromLatLon(46.13418, -63.84656), {0., 0.},
        MercatorBounds::FromLatLon(46.26739,-63.63907), 23000.);
    // And backward case
    integration::CalculateRouteAndTestRouteLength(
        integration::GetOsrmComponents(), MercatorBounds::FromLatLon(46.26739, -63.63907), {0., 0.},
        MercatorBounds::FromLatLon(46.13418, -63.84656), 23000.);
  }

  UNIT_TEST(RussiaFerryToCrimea)
  {
    // Forward
    integration::CalculateRouteAndTestRouteLength(
        integration::GetOsrmComponents(), MercatorBounds::FromLatLon(45.38053, 36.73226), {0., 0.},
        MercatorBounds::FromLatLon(45.36078, 36.60866), 13150.);
    // And backward case
    integration::CalculateRouteAndTestRouteLength(
        integration::GetOsrmComponents(), MercatorBounds::FromLatLon(45.36078, 36.60866), {0., 0.},
        MercatorBounds::FromLatLon(45.38053, 36.73226), 13110.);
  }

  UNIT_TEST(ParisCrossDestinationInForwardHeapCase)
  {
    // Forward
    integration::CalculateRouteAndTestRouteLength(
        integration::GetOsrmComponents(), MercatorBounds::FromLatLon(49.85015, 2.24296), {0., 0.},
        MercatorBounds::FromLatLon(48.85860, 2.34784), 126000.);
    // And backward case
    integration::CalculateRouteAndTestRouteLength(
        integration::GetOsrmComponents(), MercatorBounds::FromLatLon(48.85860, 2.34784), {0., 0.},
        MercatorBounds::FromLatLon(49.85015, 2.24296), 126000.);
  }

  UNIT_TEST(RussiaSmolenskRussiaMoscowTimeTest)
  {
    TRouteResult const routeResult = integration::CalculateRoute(
        integration::GetOsrmComponents(), {32.05489, 65.78463}, {0., 0.}, {37.60169, 67.45807});

    Route const & route = *routeResult.first;
    IRouter::ResultCode const result = routeResult.second;
    TEST_EQUAL(result, IRouter::NoError, ());

    integration::TestRouteTime(route, 17450.);
  }

  UNIT_TEST(RussiaMoscowLenigradskiy39GeroevPanfilovtsev22TimeTest)
  {
    TRouteResult const routeResult = integration::CalculateRoute(
        integration::GetOsrmComponents(), {37.53804, 67.53647}, {0., 0.}, {37.40990, 67.64474});

    Route const & route = *routeResult.first;
    IRouter::ResultCode const result = routeResult.second;
    TEST_EQUAL(result, IRouter::NoError, ());

    integration::TestRouteTime(route, 910.);
  }
}  // namespace
