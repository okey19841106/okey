/********************************************************************
	created:	2012/12/12
	created:	12-12-2012   23:37
	author:		okey
	
	purpose:	math template
*********************************************************************/

#include "Types.h"

namespace template
{

	template< uint32 N >
	struct Fib
	{
		enum
		{
			Val = Fib< N - 1 >::Val + Fib< N - 2 >::Val
		};
	};

	template<> struct Fib< 0 >{enum{Val = 0};};
	template<> struct Fib< 1 >{enum{Val = 1};};


#define FibT(n) Fib< n >::Val //ì³²¨ÄÉÆõº¯Êý

	template< uint32 N >
	struct Fact
	{
		enum{ Val = N * Fact< N - 1>::Val};
	};

	template<> struct Fact< 1 > {enum{ Val = 1 }; };

#define FactT(n) Fact< n >::Val //½×³Ë

	template< f64& r, int i, int max>
	struct Series
	{
		enum
		{
			// Continue is true until we've evaluated M terms
			Continue = i + 1 != max,
			NxtI = ( i + 1 ) * Continue,
			NxtMaxTerms = max * Continue
		};

		static inline double val()
		{
			return 1 - r * r / (2.0 * i + 2.0) / 
				(2.0 * i + 3.0) * Series< r * Continue, NxtI, NxtMaxTerms >::val();
		}
	};

	template<f64& r> 
	struct Sine
	{
		enum{MaxTerms = 10;};
		static inline f64 sin()
		{
			return r * Series< r, 0 , MaxTerms>::val();
		}
	};

	template <> struct Series< 0.0, 0, 0 >
	{
		static inline double val() { return 1.0; }
	};

	#define SineT( r ) Sine< r >::sin() // ÕýÏÒº¯Êý¡£

	template < double& R > struct NrSine
	{
		// All values known at compile time.
		// A decent compiler should be able to reduce to a single constant.
		static inline double sin()
		{
			double Rsqr = R * R;
			return R * ( 1.0 - Rsqr / 2.0  / 3.0
				* ( 1.0 - Rsqr / 4.0  / 5.0
				* ( 1.0 - Rsqr / 6.0  / 7.0
				* ( 1.0 - Rsqr / 8.0  / 9.0
				* ( 1.0 - Rsqr / 10.0 / 11.0
				* ( 1.0 - Rsqr / 12.0 / 13.0
				* ( 1.0 - Rsqr / 14.0 / 15.0
				* ( 1.0 - Rsqr / 16.0 / 17.0
				* ( 1.0 - Rsqr / 18.0 / 19.0
				* ( 1.0 - Rsqr / 20.0 / 21.0 
				) ) ) ) ) ) ) ) ) );
		}
	};

	// Make the template appear like a function
#define SineN( r ) NrSine< r >::sin() //·ÇµÝ¹éÕýÏÒº¯Êý¡£

	template < double& R > struct NrCos
	{
		// All values known at compile time.
		// A decent compiler should be able to reduce to a single constant.
		static inline double cos()
		{
			double Rsqr = R * R;
			return     ( 1.0 - Rsqr / 2.0
				* ( 1.0 - Rsqr / 3.0  / 4.0
				* ( 1.0 - Rsqr / 5.0  / 6.0
				* ( 1.0 - Rsqr / 7.0  / 8.0
				* ( 1.0 - Rsqr / 9.0  / 10.0
				* ( 1.0 - Rsqr / 11.0 / 12.0
				* ( 1.0 - Rsqr / 13.0 / 14.0
				* ( 1.0 - Rsqr / 15.0 / 16.0
				* ( 1.0 - Rsqr / 17.0 / 18.0
				* ( 1.0 - Rsqr / 19.0 / 20.0 
				* ( 1.0 - Rsqr / 21.0 / 22.0 
				) ) ) ) ) ) ) ) ) ) );
		}
	};

	// Make the template appear like a function
#define CosN( r ) NrCos< r >::cos() //·ÇµÝ¹éÓàÏÒº¯Êý

	///////////////////////////////////////////////////////////////////////////////
	//
	// Nonrecursive Tangent

	// Series expansion for tan( R ).
	// For conforming compilers, change double R to double& R

	template < double& R > struct NrTan
	{
		// All values known at compile time.
		// A decent compiler should be able to reduce to a single constant.
		static inline double tan()
		{
			return NrSine< R >::sin() / NrCos< R >::cos();
		}
	};

	// Make the template appear like a function
#define TanN( r ) NrTan< r >::tan() //·ÇµÝ¹éÕýÇÐº¯Êý

	

}