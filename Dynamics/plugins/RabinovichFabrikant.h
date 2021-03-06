/*
 * DO NOT EDIT THIS FILE.
 *
 * THIS FILE HAS BEEN AUTOMATICALLY GENERATED.
 * ANY CHANGES MADE TO THE CODE WILL BE LOST.
 *
 * TO MODIFY THE PARAMETER VALUES OR DYNAMICAL
 * EQUATIONS EDIT THE XML FILE (dynamics.xml).
 * 
 */
 
#ifndef RABINOVICHFABRIKANT_INCLUDED_
#define RABINOVICHFABRIKANT_INCLUDED_

#include "BaseModel.h"
#include "RungeKutta4.h"

#include "RabinovichFabrikantParameterDialog.h"

class RabinovichFabrikant : public DynamicalModel
{
  Scalar gamma;
  Scalar alpha;
public:
  RabinovichFabrikant(Scalar Gamma, Scalar Alpha)
     : gamma(Gamma), alpha(Alpha)
  { }

  virtual ~RabinovichFabrikant() { }

  virtual Vector exact(const Point& p) const
    {
      return Vector(p[1]*(p[2]-1.0+p[0]*p[0])+gamma*p[0],p[0]*(3.0*p[2]+1.0-p[0]*p[0])+gamma*p[1],-2.0*p[2]*(alpha+p[0]*p[1]));
    }

private:
  virtual void _setValue(const std::string& name, Scalar value)
    {
      if      (name == "gamma") gamma = value;
      else if (name == "alpha") alpha = value;
    }
};

class RabinovichFabrikantIntegrator : public Integrator
{
  RabinovichFabrikant* dynamics;
  RungeKutta4<RabinovichFabrikant>* integrator;
public:
  RabinovichFabrikantIntegrator()
    {
      dynamics = new RabinovichFabrikant(0.87, 1.1);
      double stepSize = 0.01;
      integrator = new RungeKutta4<RabinovichFabrikant>(*dynamics, stepSize);
    }

  virtual ~RabinovichFabrikantIntegrator()
    {
      delete dynamics;
      delete integrator;
    }

  inline Vector step(const Point& p)
    {
      return integrator->step(p);
    }

  virtual unsigned int getModelVersion()
    {
      return dynamics->getModelVersion();
    }

  virtual CaveDialog* createParameterDialog(GLMotif::PopupMenu *parent)
    {
      return new RabinovichFabrikantParameterDialog(parent, dynamics);
    }

  virtual Vrui::Point center() const
    {
      return Vrui::Point(0.0, 0.0, 0.0);
    }
};

#endif
