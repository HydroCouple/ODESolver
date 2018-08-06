/*!
*  \file    ODESolverTest.cpp
*  \author  Caleb Amoa Buahin <caleb.buahin@gmail.com>
*  \version 1.0.0
*  \section Description
*  This file and its associated files and libraries are free software;
*  you can redistribute it and/or modify it under the terms of the
*  Lesser GNU Lesser General Public License as published by the Free Software Foundation;
*  either version 3 of the License, or (at your option) any later version.
*  fvhmcompopnent.h its associated files is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.(see <http://www.gnu.org/licenses/> for details)
*  \date 2018
*  \pre
*  \bug
*  \todo Test transport on branching networks
*  \warning
*/

#include "stdafx.h"
#include "test/odesolvertest.h"
#include "odesolver.h"

void ODESolverTest::solveODEEuler_Prob1()
{
  QBENCHMARK
  {
    ODESolver solver(1, ODESolver::EULER);
    solver.initialize();

    double y = -1.0;
    double y_out = y;
    double t = 0.0;
    double dt = 0.01;
    double maxt = 1.1;

    double error = 0.0;

    while(t + dt < maxt)
    {
      solver.solve(&y, 1, t, dt, &y_out, &ODESolverTest::derivativeProb1, nullptr);

      double y_anal = problem1(t + dt);
      double currError = (y_out - y_anal);
      error += currError * currError;

      t += dt;
      y = y_out;
    }

    error = sqrt(error);

    QVERIFY2( error < 1e-4 , QString("Euler Problem 1 Error: %1").arg(error).toStdString().c_str());
  }
}

void ODESolverTest::solveODERK4_Prob1()
{
  QBENCHMARK
  {
    ODESolver solver(1, ODESolver::RK4);
    solver.initialize();

    double y = -1.0;
    double y_out = y;
    double t = 0.0;
    double dt = 0.01;
    double maxt = 1.1;

    double error = 0.0;

    while(t + dt < maxt)
    {
      solver.solve(&y, 1, t, dt, &y_out, &ODESolverTest::derivativeProb1, nullptr);

      double y_anal = problem1(t + dt);
      double currError = (y_out - y_anal);
      error += currError * currError;

      t += dt;
      y = y_out;
    }

    error = sqrt(error);

    QVERIFY2( error < 1e-4 , QString("RK4 Problem 1 Error: %1").arg(error).toStdString().c_str());
  }
}

void ODESolverTest::solveODERKQS_Prob1()
{

  ODESolver solver(1, ODESolver::RKQS);
  solver.setRelativeTolerance(1e-5);
  solver.initialize();

  double y = -1.0;
  double y_out = y;
  double t = 0.0;
  double dt = 0.01;
  double maxt = 1.1;

  double error = 0.0;

  while(t + dt < maxt)
  {
    solver.solve(&y, 1, t, dt, &y_out, &ODESolverTest::derivativeProb1, nullptr);

    double y_anal = problem1(t + dt);

    double currError = (y_out - y_anal);
    error += currError * currError;

    t += dt;
    y = y_out;
  }

  error = sqrt(error);

  QVERIFY2( error < 1e-4 , QString("RKQS Problem 1 Error: %1").arg(error).toStdString().c_str());
}

#ifdef USE_CVODE

void ODESolverTest::solveODEAdams_Prob1()
{

  QBENCHMARK
  {
    ODESolver solver(1, ODESolver::CVODE_ADAMS);
    solver.setRelativeTolerance(1e-10);
    solver.setAbsoluteTolerance(1e-16);
    solver.setOrder(12);
    solver.initialize();

    double y = -1.0;
    double y_out = y;
    double t = 0.0;
    double dt = 0.001;
    double maxt = 1.1;

    double error = 0.0;

    while(t + dt < maxt)
    {
      solver.solve(&y, 1, t, dt, &y_out, &ODESolverTest::derivativeProb1, nullptr);

      double y_anal = problem1(t + dt);

      double currError = (y_out - y_anal);
      error += currError * currError;

      t += dt;
      y = y_out;
    }

    error = sqrt(error);

    QVERIFY2( error < 1e-2 , QString("CVODE Adams Problem 1 Error: %1").arg(error).toStdString().c_str());
  }
}

void ODESolverTest::solveODEBDF_Prob1()
{

  QBENCHMARK
  {
    ODESolver solver(1, ODESolver::CVODE_BDF);
    solver.setRelativeTolerance(1e-10);
    solver.setAbsoluteTolerance(1e-16);
    solver.setOrder(5);
    solver.initialize();

    double y = -1.0;
    double y_out = y;
    double t = 0.0;
    double dt = 0.01;
    double maxt = 1.1;

    double error = 0.0;

    while(t + dt < maxt)
    {
      solver.solve(&y, 1, t, dt, &y_out, &ODESolverTest::derivativeProb1, nullptr);

      double y_anal = problem1(t + dt);

      double currError = (y_out - y_anal);
      error += currError * currError;

      t += dt;
      y = y_out;
    }

    error = sqrt(error);

    QVERIFY2( error < 1e-4 , QString("CVODE BDF Problem 1 Error: %1").arg(error).toStdString().c_str());
  }
}

#endif

void ODESolverTest::solveODEEuler_Prob2()
{
  QBENCHMARK
  {
    ODESolver solver(1, ODESolver::EULER);
    solver.initialize();

    double y = 3.0;
    double y_out = y;
    double t = 1.0;
    double dt = 0.001;
    double maxt = 5.0;

    double error = 0.0;

    while(t + dt < maxt)
    {
      solver.solve(&y, 1, t, dt, &y_out, &ODESolverTest::derivativeProb2, nullptr);

      double tdt = t + dt;
      double y_anal = problem2(tdt);

      double currError = (y_out - y_anal);
      error += currError * currError;

      t += dt;
      y = y_out;
    }

    error = sqrt(error);

    QVERIFY2( error < 1e-2 , QString("RK4 Problem 2 Error: %1").arg(error).toStdString().c_str());
  }
}

void ODESolverTest::solveODERK4_Prob2()
{
  QBENCHMARK
  {
    ODESolver solver(1, ODESolver::RK4);
    solver.initialize();

    double y = 3.0;
    double y_out = y;
    double t = 1.0;
    double dt = 0.01;
    double maxt = 5.0;

    double error = 0.0;

    while(t + dt < maxt)
    {
      solver.solve(&y, 1, t, dt, &y_out, &ODESolverTest::derivativeProb2, nullptr);

      double tdt = t + dt;
      double y_anal = problem2(tdt);

      double currError = (y_out - y_anal);
      error += currError * currError;

      t += dt;
      y = y_out;
    }

    error = sqrt(error);

    QVERIFY2( error < 1e-4 , QString("RK4 Problem 2 Error: %1").arg(error).toStdString().c_str());
  }
}

void ODESolverTest::solveODERKQS_Prob2()
{

  QBENCHMARK
  {
    ODESolver solver(1, ODESolver::RKQS);
    solver.setRelativeTolerance(1e-3);
    solver.initialize();

    double y = 3.0;
    double y_out = y;
    double t = 1.0;
    double dt = 0.01;
    double maxt = 5.0;

    double error = 0.0;

    while(t + dt < maxt)
    {
      solver.solve(&y, 1, t, dt, &y_out, &ODESolverTest::derivativeProb2, nullptr);

      double tdt = t + dt;
      double y_anal = problem2(tdt);

      double currError = (y_out - y_anal);
      error += currError * currError;

      t += dt;
      y = y_out;
    }

    error = sqrt(error);

    QVERIFY2( error < 1e-4 , QString("RKQS Problem 2 Error: %1").arg(error).toStdString().c_str());
  }
}

#ifdef USE_CVODE

void ODESolverTest::solveODEAdams_Prob2()
{
  //  printf("RKQS\n");

  QBENCHMARK
  {
    ODESolver solver(1, ODESolver::CVODE_ADAMS);
    solver.setRelativeTolerance(1e-10);
    solver.setAbsoluteTolerance(1e-16);
    solver.setOrder(10);
    solver.initialize();

    double y = 3.0;
    double y_out = y;
    double t = 1.0;
    double dt = 0.01;
    double maxt = 5.0;

    double error = 0.0;

    while(t + dt < maxt)
    {
      solver.solve(&y, 1, t, dt, &y_out, &ODESolverTest::derivativeProb2, nullptr);

      double tdt = t + dt;
      double y_anal = problem2(tdt);

      double currError = (y_out - y_anal);
      error += currError * currError;

      t += dt;
      y = y_out;
    }

    error = sqrt(error);

    QVERIFY2( error < 1e-4 , QString("CVODE ADAMS Problem 2 Error: %1").arg(error).toStdString().c_str());
  }
}

void ODESolverTest::solveODEBDF_Prob2()
{
  //  printf("RKQS\n");

  QBENCHMARK
  {
    ODESolver solver(1, ODESolver::CVODE_BDF);
    solver.setRelativeTolerance(1e-10);
    solver.setAbsoluteTolerance(1e-16);
    solver.setOrder(5);
    solver.initialize();

    double y = 3.0;
    double y_out = y;
    double t = 1.0;
    double dt = 0.01;
    double maxt = 5.0;

    double error = 0.0;

    while(t + dt < maxt)
    {
      solver.solve(&y, 1, t, dt, &y_out, &ODESolverTest::derivativeProb2, nullptr);

      double tdt = t + dt;
      double y_anal = problem2(tdt);

      double currError = (y_out - y_anal);
      error += currError * currError;

      t += dt;
      y = y_out;
    }

    error = sqrt(error);

    QVERIFY2( error < 1e-4 , QString("CVODE BDF Problem 2 Error: %1").arg(error).toStdString().c_str());
  }
}

#endif

void ODESolverTest::derivativeProb1(double t, double y[], double dydt[], void *userData)
{
  dydt[0] = t * pow(y[0],3) / sqrt(1 + t * t);
}

double ODESolverTest::problem1(double t)
{
  return -1.0 / sqrt(3.0 - 2.0 * sqrt(1+t*t));
}

void ODESolverTest::derivativeProb2(double t, double y[], double dydt[], void* userData)
{
  dydt[0] = (3 * t*t + 4 * t - 4)/(2 * y[0] - 4);
}

double ODESolverTest::problem2(double t)
{
  return 2.0 + sqrt(t*t*t + 2.0*t*t - 4.0*t + 2.0);
}
