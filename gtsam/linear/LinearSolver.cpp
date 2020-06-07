/* ----------------------------------------------------------------------------

 * GTSAM Copyright 2010, Georgia Tech Research Corporation,
 * Atlanta, Georgia 30332-0415
 * All Rights Reserved
 * Authors: Frank Dellaert, et al. (see THANKS for the full author list)

 * See LICENSE for the license information

 * -------------------------------------------------------------------------- */

/**
 * @file    LinearSolver.cpp
 * @brief   Common Interface for Linear Solvers
 * @author  Fan Jiang
 */

#include <gtsam/linear/LinearSolver.h>
#include <gtsam/linear/SparseEigenSolver.h>
#include <gtsam/linear/SuiteSparseSolver.h>

namespace gtsam {

LinearSolver::LinearSolver() = default;

boost::shared_ptr<LinearSolver> LinearSolver::fromLinearSolverParams(
    const LinearSolverParams &params) {
  if (params.linearSolverType == LinearSolverParams::EIGEN_QR) {
    return boost::shared_ptr<SparseEigenSolver>(new SparseEigenSolver(
        SparseEigenSolver::SparseEigenSolverType::QR, *params.ordering));
  } else if (params.linearSolverType == LinearSolverParams::EIGEN_CHOLESKY) {
    return boost::shared_ptr<SparseEigenSolver>(new SparseEigenSolver(
        SparseEigenSolver::SparseEigenSolverType::CHOLESKY, *params.ordering));
  } else if (params.linearSolverType == LinearSolverParams::SUITESPARSE_CHOLESKY) {
    return boost::shared_ptr<SuiteSparseSolver>(new SuiteSparseSolver(
        SuiteSparseSolver::SuiteSparseSolverType::CHOLESKY, *params.ordering));
  }

  throw std::runtime_error("Invalid parameters passed");
}
}  // namespace gtsam