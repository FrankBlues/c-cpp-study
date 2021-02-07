#include "gdal_priv.h"

int main()
{
    OGRSpatialReference geoSRS;

    // oSRS.SetGeogCS( "My geographic CRS",
    //                 "World Geodetic System 1984",
    //                 "My WGS84 Spheroid",
    //                 SRS_WGS84_SEMIMAJOR, SRS_WGS84_INVFLATTENING,
    //                 "Greenwich", 0.0,
    //                 "degree", SRS_UA_DEGREE_CONV );

    // oSRS.SetWellKnownGeogCS( "WGS84" );
    // oSRS.SetWellKnownGeogCS( "EPSG:4326" );
    // char *pszWKT = NULL;
    // oSRS.exportToWkt( &pszWKT );
    // printf( "%s\n", pszWKT );
    // CPLFree(pszWKT);

    // 定义地理坐标系
    char *pszWKT = nullptr;
    geoSRS.SetWellKnownGeogCS( "WGS84" );
    const char* apszOptions[] = { "FORMAT=WKT2_2018", "MULTILINE=YES", nullptr };
    geoSRS.exportToWkt( &pszWKT, apszOptions );
    // printf( "%s\n", pszWKT );

    // 定义投影坐标系
    OGRSpatialReference proSRS;

    proSRS.SetProjCS( "UTM 17 (WGS84) in northern hemisphere." );
    proSRS.SetWellKnownGeogCS( "WGS84" );
    proSRS.SetUTM( 17, TRUE );
    proSRS.exportToWkt( &pszWKT, apszOptions );
    // printf( "%s\n", pszWKT );
    CPLFree(pszWKT);

    // Querying Coordinate Reference System
    OGRSpatialReference  *poSRS = &proSRS;
    const char *pszProjection = poSRS->GetAttrValue("PROJECTION");

    char *szProj4 = nullptr;
    poSRS->exportToProj4(&szProj4);
    printf("%s\n%d\n", szProj4, (int)strlen(szProj4));
    // char _szProj4 [60];
    // printf("%s\n", pszProjection);
    // 段错误
    if( pszProjection == NULL )
    {
        if( poSRS->IsGeographic() )
            sprintf( szProj4+strlen(szProj4), "+proj=longlat " );
        else
            sprintf( szProj4+strlen(szProj4), "unknown " );
    }
    else if( EQUAL(pszProjection,SRS_PT_TRANSVERSE_MERCATOR) )
    {
        printf("%s\n", pszProjection);
        sprintf( szProj4+strlen(szProj4),
        "+proj=cea +lon_0=%.9f +lat_ts=%.9f +x_0=%.3f +y_0=%.3f ",
                poSRS->GetProjParm(SRS_PP_CENTRAL_MERIDIAN,0.0),
                poSRS->GetProjParm(SRS_PP_STANDARD_PARALLEL_1,0.0),
                poSRS->GetProjParm(SRS_PP_FALSE_EASTING,0.0),
                poSRS->GetProjParm(SRS_PP_FALSE_NORTHING,0.0) );
    }
    CPLFree(szProj4);


    // OGRSpatialReference oSourceSRS, oTargetSRS;
    // OGRCoordinateTransformation *poCT;
    // double x, y;

    // oSourceSRS.importFromEPSG( atoi(papszArgv[i+1]) );
    // oTargetSRS.importFromEPSG( atoi(papszArgv[i+2]) );

    // poCT = OGRCreateCoordinateTransformation( &oSourceSRS,
    //                                         &oTargetSRS );
    // x = atof( papszArgv[i+3] );
    // y = atof( papszArgv[i+4] );

    // if( poCT == NULL || !poCT->Transform( 1, &x, &y ) )
    //     printf( "Transformation failed.\n" );
    // else
    // {
    //     printf( "(%f,%f) -> (%f,%f)\n",
    //             atof( papszArgv[i+3] ),
    //             atof( papszArgv[i+4] ),
    //             x, y );
    // }
}