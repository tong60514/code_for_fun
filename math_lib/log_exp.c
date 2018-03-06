double exp(double power){
	double res = (1.0+(power/18384.0));
	res*=res;
	res*=res;
	res*=res;
	res*=res;
	res*=res;
	res*=res;
	res*=res;
	res*=res;
	res*=res;
	res*=res;
	res*=res;
	res*=res;
	res*=res;
	return res;
}

double ln(double f){

	double xn = 2.0;
	for(int i=0;i<100;i++){
		xn = xn - ((exp(xn)-f)/(xn*exp(xn)));
	}
	return xn;
}

double power(double base,double power){
	return exp(power*ln(base));
}
