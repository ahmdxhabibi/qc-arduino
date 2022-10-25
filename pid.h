double Ei;
float getPID (float mbarVal, float target)
{
  input = mbarVal;
  sp = target;
  error = sp - input;
  if (error < 0)
  {
    
  }
  Ei = (error * 0.005) + Ei;
  if (Ei > 120)
  {
    Ei = 120;
  }
  if (Ei < -120)
  {
    Ei = -120;
  }
  u = (1.2 * error) + (1.1 * Ei);  //+ (0.1 * (error - Ex) 
  u = constrain (u, 0, 255);
  Ex = error;
  return u;
}
