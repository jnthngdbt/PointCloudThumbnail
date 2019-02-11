#include "stdafx.h"

#include <math.h>
#include <stdlib.h>

#include <string>
#include <vector>

#include <pcl/pcl_base.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/obj_io.h>
#include <pcl/visualization/pcl_visualizer.h>

int main(int argc, char* argv[])
{
    for (int i = 1; i < argc; ++i) // argv[0] is the path to the program, we want from argv[1] onwards
    {
        const std::string filename(argv[i]);
        const std::string ext = filename.substr(filename.size() - 4);

        std::cout << filename << std::endl;

        pcl::PointCloud<pcl::PointXYZ> cloud;
        if (ext == ".pcd") pcl::io::loadPCDFile(filename, cloud);
        else if (ext == ".obj") pcl::io::loadOBJFile(filename, cloud);

        pcl::visualization::PCLVisualizer viewer (filename);
        viewer.addPointCloud(cloud.makeShared(), filename);

        viewer.spin(); // TBR
    }

    return 0;
}

//using PointsType = pcl::PointCloud<pcl::PointXYZ>;
//
//int main()
//{
//    PointsType::Ptr cloudModel = makeCloud();
//
//    // Noisy cloud.
//    PointsType::Ptr cloudNoisy = makeCloud();
//    for (auto& p : cloudNoisy->points)
//        p.z += 0.05*randf();
//
//    // Transformed cloud.
//    PointsType::Ptr cloudMoved (new PointsType());
//    Eigen::Affine3f T = Eigen::Affine3f::Identity();
//    T.translate(Eigen::Vector3f(0.05, 0, 0));
//    pcl::transformPointCloud(*cloudModel, *cloudMoved, T);
//
//    // Normals.
//    using NormalsType = pcl::PointCloud<pcl::Normal>;
//    NormalsType::Ptr normals(new NormalsType());
//    pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> ne;
//    ne.setInputCloud(cloudModel);
//    ne.setKSearch(30);
//    ne.compute(*normals);
//
//    // Patches.
//    pcl::PassThrough<pcl::PointXYZ> ptf;
//    PointsType::Ptr cloudPatch1(new PointsType());
//    ptf.setInputCloud(cloudModel);
//    ptf.setFilterFieldName("x");
//    ptf.setFilterLimits(0.3, 0.5);
//    ptf.filter(*cloudPatch1);
//    ptf.setInputCloud(cloudPatch1);
//    ptf.setFilterFieldName("y");
//    ptf.setFilterLimits(0.4, 0.5);
//    ptf.filter(*cloudPatch1);
//
//    // Some array features.
//    const int N = cloudModel->size();
//    std::vector<float> idx(N);
//    std::vector<float> idxn(N);
//    std::vector<float> rnd(N);
//    std::vector<float> rnd2(N);
//    for (int i = 0; i < N; ++i)
//    {
//        idx[i] = (float)i;
//        idxn[i] = idx[i] / (float)N;
//        rnd[i] = randf();
//        rnd2[i] = randf();
//    }
//
//    std::cout << *cloudModel << std::endl;
//    pcl::io::savePCDFile("cloud.pcd", *cloudModel);
//
//    auto multipleViewports = [&]()
//    {
//        VISUALIZER_CALL(Visualizer viewer("multiple-viewports", 2, 3));
//
//        std::string NAME;
//        int viewport = 0;
//
//        NAME = "add-feature-multiplecalls"; 
//        VISUALIZER_CALL(viewer.addCloud(*cloudModel, NAME));
//        VISUALIZER_CALL(viewer.addFeature(idx, "index", NAME));
//        viewport++;
//
//        NAME = "add-feature-chained";
//        VISUALIZER_CALL(viewer.addCloud(*cloudNoisy, NAME, viewport).addFeature(rnd, "randv").addFeature(idx, "index"));
//        viewport++;
//
//        NAME = "add-feature-cloud-to-cloud-multiplecalls";
//        VISUALIZER_CALL(viewer.addCloud(*cloudModel, NAME, viewport).addFeature(rnd, "randv"));
//        VISUALIZER_CALL(viewer.addCloud(*normals, NAME, viewport));
//        viewport++;
//
//        NAME = "add-feature-lamdba-to-cloud-chained";
//        VISUALIZER_CALL(viewer.addCloud(*cloudNoisy, NAME, viewport)
//            .addFeature(normals->points, "c", [](const pcl::Normal& p) { return p.curvature; }));
//        viewport++;
//
//        NAME = "add-feature-lamdba-to-cloud-multiplecalls";
//        VISUALIZER_CALL(viewer.addFeature(cloudModel->points, "x", NAME, [](const pcl::PointXYZ& p) { return p.x; }, viewport));
//        VISUALIZER_CALL(viewer.addFeature(cloudModel->points, "y", NAME, [](const pcl::PointXYZ& p) { return p.y; }, viewport));
//        VISUALIZER_CALL(viewer.addFeature(cloudModel->points, "z", NAME, [](const pcl::PointXYZ& p) { return p.z; }, viewport));
//        VISUALIZER_CALL(viewer.addSpace("x", "y", "z", NAME));
//        viewport++;
//
//        NAME = "multiple-clouds-properties-multiplecalls";
//        VISUALIZER_CALL(viewer.addCloud(*cloudModel, NAME + "-0", viewport).addFeature(idx, "index").addCloud(*normals).setColor(1.0, 0.0, 0.0).setOpacity(0.5).setSize(5));
//        VISUALIZER_CALL(viewer.addCloud(*cloudNoisy, NAME + "-1", viewport));
//        viewport++;
//
//        VISUALIZER_CALL(viewer.render());
//    };
//
//    auto singleViewport = [&]()
//    {
//        VISUALIZER_CALL(Visualizer viewer("single-viewport"));
//
//        VISUALIZER_CALL(viewer.addCloud(*cloudNoisy, "scan").setOpacity(0.4));
//        VISUALIZER_CALL(viewer.addCloud(*cloudModel, "model").addCloud(*normals).setOpacity(0.7));
//        VISUALIZER_CALL(viewer.addCloud(*cloudPatch1, "patch").setColor(1, 0, 0).setSize(3));
//
//        VISUALIZER_CALL(viewer.render());
//    };
//
//    auto singleViewportGeometryHandlers = [&]()
//    {
//        VISUALIZER_CALL(Visualizer viewer("single-viewport-geometry-handlers"));
//
//        // TODO add method  viewer.addSpace("u1", "u2", "u3", name).
//
//        std::string name = "space";
//        VISUALIZER_CALL(viewer.addFeature(idxn, "u1", name));
//        VISUALIZER_CALL(viewer.addFeature(rnd, "u2", name));
//        VISUALIZER_CALL(viewer.addFeature(rnd2, "u3", name));
//        VISUALIZER_CALL(viewer.addSpace("u1", "u2", "u3", name).addCloud(*normals));
//
//        VISUALIZER_CALL(viewer.render());
//    };
//
//    auto storeCloudsInClouds = [&]()
//    {
//        VISUALIZER_CALL(Visualizer viewer("store-clouds-in-clouds", 1, 2));
//
//        VISUALIZER_CALL(viewer.addCloud(*cloudModel, "model").addCloud(*normals).setOpacity(0.7));
//
//        using KdTree = pcl::search::KdTree<pcl::PointXYZ>;
//        KdTree::Ptr tree(new KdTree());
//        tree->setInputCloud(cloudModel);
//
//        int i = 0;
//
//        for (const auto& p : *cloudModel)
//        {
//            std::vector<int> pi;
//            tree->nearestKSearch(p, 10, pi, FeatureData());
//
//            PointsType::Ptr neigh(new PointsType(*cloudModel, pi));
//            VISUALIZER_CALL(viewer.addCloudIndexed(*neigh, "model", i++, "neighborhood", 1).setSize(5));
//        }
//
//        VISUALIZER_CALL(viewer.render());
//    };
//
//    // TODO delete files at render
//
//    singleViewport();
//    multipleViewports();
//    singleViewportGeometryHandlers();
//    storeCloudsInClouds();
//
//    return 0;
//}
//
