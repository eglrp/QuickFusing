#include <iostream>
#include <fstream>
#include <cmath>



#include <eigen3/Eigen/Dense>

#include "CSVReader.h"
#include "matplotlib_interface.h"

#include "SettingPara.h"
#include "EKF.hpp"


namespace plt = matplotlibcpp;

int main() {

    /*
     * Load Imu data.
     */
    std::string dir_name = "tmp_file_dir/";

    CSVReader ImuDataReader(dir_name + "ImuData.data.csv"),ZuptReader(dir_name + "Zupt.data.csv");

    auto ImuDataTmp(ImuDataReader.GetMatrix()),ZuptTmp(ZuptReader.GetMatrix());

    Eigen::MatrixXd ImuData,Zupt;
    ImuData.resize(ImuDataTmp.GetRows(),ImuDataTmp.GetCols());
    Zupt.resize(ZuptTmp.GetRows(),ZuptTmp.GetCols());

    for(int i(0);i<ImuDataTmp.GetRows();++i)
    {
        for(int j(0);j<ImuDataTmp.GetCols();++j)
        {
            ImuData(i,j) = *ImuDataTmp(i,j);
        }
        Zupt(i,0) = *ZuptTmp(i,0);
    }


    /*
     * Set initial parameter for ekf.
     */
    SettingPara init_para(true);

    init_para.init_pos1_ = Eigen::Vector3d(0.8, -5.6, 0.0);
    init_para.init_heading1_ = -180 / 180 * M_PI;

    init_para.Ts_ = 1.0 / 128.0;

    /*
     * Initial filter.
     */
    Ekf ekf(init_para);

    ekf.InitNavEq(ImuData.block(0, 1, 20, 6));

    std::vector<double> imux, imuy;
    for (int i(0); i < ImuData.rows(); ++i) {

        Eigen::VectorXd vec = ekf.GetPosition(ImuData.block(i, 1, 1, 6).transpose(), Zupt(i));
        if (isnan(vec(0))) {
            std::cout << "ddd" << std::endl;
            MYERROR("value change to nan")
            break;

        } else {
            imux.push_back(double(vec(0)));
            imuy.push_back(double(vec(1)));
        }
        std::cout << i << ":" << ImuData.rows() << ":" << Zupt(i) << "   :   " << vec.transpose() << std::endl;
    }



    /*
     * Load uwb data.
     */
    






//    plt::subplot(2,1,1);
    plt::named_plot("result", imux, imuy, "r+-");
    plt::grid(true);
    plt::show();





    return 0;


}