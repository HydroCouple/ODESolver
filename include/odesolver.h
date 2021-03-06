/*!
 *  \file    odesolver.h
 *  \author  Caleb Amoa Buahin <caleb.buahin@gmail.com>
 *  \version 1.0.0
 *  \section Description
 *  Runge Kutta solves from
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
 *  \todo
 *  \warning
 */


#ifndef ODESOLVER_H
#define ODESOLVER_H

#include "odesolver_global.h"

#ifdef USE_CVODE
#include <cvode/cvode.h>
#include <sundials/sundials_linearsolver.h>
#endif

#include <vector>

class ODESolver;

/*!
 *
 */
typedef void (*ComputeDerivatives)(double t, double y[], double dydt[], void* userData);

/*!
 *
 */
typedef int (ODESolver::*Solve)(double y[], int n, double t, double dt, double yout[], ComputeDerivatives derivs, void* userData);


#ifdef USE_CVODE

struct ODESOLVER_EXPORT RedirectionData
{
    ComputeDerivatives deriv;
    void *userData;
};

#endif

class ODESOLVER_EXPORT ODESolver
{

  public:

    /*!
     * \brief The SolverType enum
     */
    enum SolverType
    {
      EULER,
      RK4,
      RKQS,
#ifdef USE_CVODE
      CVODE_ADAMS,
      CVODE_BDF
#endif
    };

    enum IterationMethod
    {
      FUNCTIONAL = 1,
      NEWTON = 2
    };

    enum LinearSolverType
    {
      GMRES, //scaled, preconditioned GMRES
      FGMRES,
      Bi_CGStab,
      TFQMR,
      PCG,
    };


    /*!
     * \brief ODESolver
     * \param maxSize
     * \param solverType
     */
    ODESolver(int size, SolverType solverType);

    ~ODESolver();

    /*!
     * \brief initialize
     */
    void initialize();

    /*!
     * \brief initializeLinearSolver
     */
    void initializeLinearSolver();

    /*!
     * \brief initializeNonLinearSolver
     */
    void initializeNonLinearSolver();

    /*!
     * \brief size
     * \return
     */
    int size() const;

    /*!
     * \brief setSize
     * \param size
     */
    void setSize(int size);

    /*!
     * \brief solverType
     * \return
     */
    SolverType solverType() const;

    /*!
     * \brief setSolverType
     * \param solverType
     */
    void setSolverType(SolverType solverType);

    /*!
     * \brief solverIterationMethod
     * \return
     */
    IterationMethod solverIterationMethod() const;

    /*!
     * \brief setSolverIterationMethod
     * \param iterationMethod
     */
    void setSolverIterationMethod(IterationMethod iterationMethod);

    /*!
     * \brief linearSolverType
     * \return
     */
    LinearSolverType linearSolverType() const;

    /*!
     * \brief setLinearSolverType
     * \param linearSolverType
     */
    void setLinearSolverType(LinearSolverType linearSolverType);

    /*!
     * \brief maxIterations
     * \return
     */
    int maxIterations() const;

    /*!
     * \brief setMaxIterations
     * \param iterations
     */
    void setMaxIterations(int iterations);

    /*!
     * \brief getIterations
     * \return
     */
    int getIterations() const;

    /*!
     * \brief order
     * \return
     */
    int order() const;

    /*!
     * \brief setOrder
     * \param order
     */
    void setOrder(int order);

    /*!
     * \brief relativeTolerance
     * \return
     */
    double relativeTolerance() const;

    /*!
     * \brief setRelativeTolerance
     * \param tolerance
     */
    void setRelativeTolerance(double tolerance);

    /*!
     * \brief absoluteTolerance
     * \return
     */
    double absoluteTolerance() const;

    /*!
     * \brief setAbsoluteTolerance
     * \param tolerance
     */
    void setAbsoluteTolerance(double tolerance);

    /*!
     * \brief solve
     * \param y
     * \param n
     * \param t
     * \param dt
     * \param yout
     * \param derivs
     * \param userData
     * \return
     */
    int solve(double y[], int n, double t, double dt, double yout[], ComputeDerivatives derivs, void* userData);

  private:

    /*!
     * \brief euler
     * \param y
     * \param n
     * \param t
     * \param dt
     * \param yout
     * \param derivs
     * \param userData
     * \return
     */
    int euler(double y[], int n, double t, double dt, double yout[], ComputeDerivatives derivs, void* userData);

    /*!
     * \brief rk4 Given values for the variables y[1..n] and their derivatives dydx[1..n] known at t, use the
     fourth-order Runge-Kutta method to advance the solution over an interval dt and return the
     incremented variables as yout[1..n], which need not be a distinct array from y. The user
     supplies the routine derivs(t,y,dydt), which returns derivatives dydt at t.
     * \param y
     * \param n
     * \param t
     * \param dt
     * \param yout
     * \param derivs
     * \param userData
     * \return
     */
    int rk4(double y[], int n, double t, double dt, double yout[], ComputeDerivatives derivs, void* userData);

    /*!
     * \brief rkqsDriver Driver function for Runge-Kutta integration with adaptive
      stepsize control. Integrates starting n values in y[]
      from t to t+dt with accuracy eps. h1 is the initial stepsize
      guess and derivs is a user-supplied function that computes
      derivatives dy/dx of y. On completion, yout contains the
      new values of y at the end of the integration interval.
     * \param y
     * \param n
     * \param t
     * \param dt
     * \param yout
     * \param derivs
     * \param userData
     * \return
     */
    int rkqsDriver(double y[], int n, double t, double dt, double yout[], ComputeDerivatives derivs, void* userData);

    /*!
     * \brief rkqs Fifth-order Runge-Kutta integration step with monitoring of
      local truncation error to assure accuracy and adjust stepsize.
      Inputs are current value of t, trial step size (dtTry), and
      accuracy (eps). Outputs are stepsize taken (dtDid) and estimated
      next stepsize (dtNext). Also updated are the values y[].
     * \param t
     * \param dydt
     * \param yout
     * \param n
     * \param dtTry
     * \param dtDid
     * \param dtNext
     * \param derivs
     * \param userData
     * \return
     */
    int rkqs(double *t, double dydt[], double yout[], int n, double dtTry, double *dtDid, double *dtNext, ComputeDerivatives derivs, void* userData);

    /*!
     * \brief rkck Uses the Runge-Kutta-Cash-Karp method to advance y[] at x
       over stepsize h.
     * \param t
     * \param dydt
     * \param yout
     * \param n
     * \param dt
     * \param deriv
     * \param userData
     */
    void rkck(double t, double dydt[],  double yout[], int n, double dt, ComputeDerivatives deriv, void* userData);

#ifdef USE_CVODE

    /*!
     * \brief solveCVODE
     * \param y
     * \param n
     * \param t
     * \param dt
     * \param yout
     * \param derivs
     * \param userData
     */
    int solveCVODE(double y[], int n, double t, double dt, double yout[], ComputeDerivatives derivs, void* userData);

    /*!
     * \brief ComputeDerivatives_CVODE
     * \param t
     * \param y
     * \param dydt
     * \param user_data
     * \return
     */
    static int ComputeDerivatives_CVODE(realtype t, N_Vector y, N_Vector dydt, void *user_data);

#endif

    /*!
     * \brief clearMemory
     */
    void clearMemory();


  private:

    int m_size,
    m_maxSteps,
    m_order,
    m_currentIterations;

    //RK4 Parameters
    double m_safety,
    m_pgrow,
    m_pshrnk,
    m_errcon,
    m_relTol,
    m_absTol,
    *m_yscal,
    *m_yerr,
    *m_ytemp,
    *m_ak;

    SolverType m_solverType;
    Solve m_solver;

#ifdef USE_CVODE
    void* m_cvodeSolver;
    IterationMethod m_solverIterationMethod;
    LinearSolverType m_linearSolverType;
    SUNLinearSolver m_linearSolver;
    SUNNonlinearSolver m_nonLinearSolver;
    N_Vector m_cvy;
#endif

};







#endif // ODESOLVER_H
