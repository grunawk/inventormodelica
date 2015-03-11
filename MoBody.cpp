#include "stdafx.h"
#include "MoBody.h"
#include "MoBodyFrame.h"

static double gap = 20.0;
static double width = 20.0;
static double height = 20.0;

MoId MoBody::m_lastId = 0;

std::string toBase64 (BYTE const * bytes, size_t length)
// converts the bytes array into a base64 string
{
	std::string output;

	// NOTE: If your implementation of base64 must use a slightly different alphabet, you must
	// change it here and in base64decode.
	static const char *const alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
		
	output.clear();
	output.reserve((4 * length + 2) / 3); // Any changes to the algorithm would likely change this as well
	int tmp;
	const unsigned char *cur = (const unsigned char *)bytes;
	const unsigned char *end = cur + length;
	while(end - cur >= 3)
	{
		output += alphabet[(*cur >> 2) & 0x3F];
		tmp = (*cur++ << 4) & 0x30;
		output += alphabet[tmp | ((*cur >> 4) & 0x0F)];
		tmp = (*cur++ << 2) & 0x3C;
		output += alphabet[tmp | ((*cur >> 6) & 0x03)];
		output += alphabet[*cur++ & 0x3F];
	}

	if(end - cur)
	{
		output += alphabet[(*cur >> 2) & 0x3F];
		if(end - cur > 1)
		{
			tmp = (*cur++ << 4) & 0x30;
			output += alphabet[tmp | ((*cur >> 4) & 0x0F)];
			if(end - cur > 1)
			{
				tmp = (*cur++ << 2) & 0x3C;
				output += alphabet[tmp | ((*cur >> 6) & 0x03)];
				output += alphabet[*cur & 0x3F];
			}
			else
				output += alphabet[(*cur << 2) & 0x3C];
		}
		else
		{
			output += alphabet[(*cur << 4) & 0x30];
		}
	}

	// Apply padding the way that windows base 64 encoder does...
	size_t encodedSize = output.size();
	while(encodedSize % 4)
	{
		output += "=";
		encodedSize++;
	}

	return output;
}

HRESULT render(IPicture* piPicture, BYTE*&bytes, size_t &len )
{
	HRESULT hr = NOERROR;

	// Set up the bitmap info...
	LONG dwWidth = 200, dwHeight = 200;
	BITMAPINFO bminfo;
	bminfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bminfo.bmiHeader.biWidth = dwWidth;
	bminfo.bmiHeader.biHeight = dwHeight;
	bminfo.bmiHeader.biPlanes = 1;
	bminfo.bmiHeader.biBitCount = 24;
	bminfo.bmiHeader.biCompression = BI_RGB;
	bminfo.bmiHeader.biSizeImage = 0; // 0 for BI_RGB compression
	bminfo.bmiHeader.biXPelsPerMeter = 2835 ;
	bminfo.bmiHeader.biYPelsPerMeter = 2835 ;
	bminfo.bmiHeader.biClrUsed = 0;
	bminfo.bmiHeader.biClrImportant = 0;

	// Create the storage stream...
	IStream* piStream = NULL;
	hr = ::CreateStreamOnHGlobal( NULL, TRUE, &piStream );

	// Render it...
	LPVOID pBits=NULL;
	HBITMAP hBitmap = ::CreateDIBSection(NULL, &bminfo, DIB_RGB_COLORS, &pBits, NULL, 0);
	CDC memDC;
	VERIFY(memDC.CreateCompatibleDC(NULL));
	CBitmap bitmap;
	bitmap.Attach(hBitmap);
	CBitmap *pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.SetMapMode(MM_TEXT);
	OLE_YSIZE_HIMETRIC height;
	OLE_XSIZE_HIMETRIC width;
	hr = piPicture->get_Height(&height);
	ASSERT(SUCCEEDED(hr));
	hr = piPicture->get_Width(&width);
	ASSERT(SUCCEEDED(hr));
	hr = piPicture->Render(memDC.m_hDC, 0, dwWidth, dwHeight, -dwWidth, 0,0, width, height,NULL);
	ASSERT(SUCCEEDED(hr));
	memDC.SelectObject(pOldBitmap);
	
	// Create the bitmap header...
	PICTDESC pictDesc;
	pictDesc.cbSizeofstruct = sizeof(PICTDESC);
	pictDesc.bmp.hbitmap = (HBITMAP)bitmap.m_hObject;
	pictDesc.bmp.hpal = NULL;
	pictDesc.picType = PICTYPE_BITMAP;

	// Write it to the stream...
	IUnknownPtr punkPicture;
	hr = OleCreatePictureIndirect(&pictDesc,IID_IUnknown,FALSE,(LPVOID*)&punkPicture);
	ASSERT(SUCCEEDED(hr));
	IPicturePtr spiNewPicture = punkPicture;
	hr = spiNewPicture->SaveAsFile(piStream,TRUE,NULL);
	ASSERT(SUCCEEDED(hr));

	// Read the bytes in the stream...
	STATSTG stgStat;
	LARGE_INTEGER liZero;
	liZero.QuadPart = 0;
	piStream->Seek( liZero,  STREAM_SEEK_SET, NULL );
	piStream->Stat( &stgStat, STATFLAG_NONAME );
	bytes = new BYTE[(ULONG)stgStat.cbSize.QuadPart];
	ULONG ulBytesRead = 0;
	piStream->Read( (LPVOID)bytes, (ULONG)stgStat.cbSize.QuadPart, &ulBytesRead );
	len = ulBytesRead;

	return NOERROR;
}

MoBody::MoBody(void) :
	MoBase(++m_lastId),
	m_transform(AcGeMatrix3d::kIdentity),
	m_cg(AcGePoint3d::kOrigin),
	m_mass(0.0)
{
	m_placement.x = gap + (m_lastId-1) * (width + gap) + width/2;
	m_placement.y = gap + height/2;
	m_width = width;
	m_height = height;
}


MoBody::~MoBody(void)
{
}

void MoBody::addMass(double mass, const AcGePoint3d& cg, const MIxInertiaTensor& inertia)
{
	m_mass += mass;
	m_cg += cg.asVector();
	m_inertia += inertia;
}

HRESULT MoBody::thumbnail(const IPictureDispPtr& pictureDisp)
{
	if (IPicturePtr pict = pictureDisp)
	{
		BYTE* bytes = nullptr;
		size_t len = 0;
		HRESULT hr = render(pict, bytes, len);
		OnErrorReturn(FAILED(hr), hr);

		m_thumbnail = toBase64(bytes, len);
		delete[] bytes;
	}

	return m_thumbnail.empty() ? E_FAIL : S_OK;
}

void MoBody::addBodyFrame(MoBodyFramePtr bodyFrame)
{
	m_bodyFrames.push_back(bodyFrame);
	bodyFrame->id(m_bodyFrames.size());
}

bool MoBody::write(FILE* moFile) const
{
	AcGePoint3d origin;
	AcGeVector3d xAxis, yAxis, zAxis;
	m_transform.getCoordSystem(origin, xAxis, yAxis, zAxis);

	double phi = atan2(m_transform(2,0), m_transform(2,1));
	double theta = acos(m_transform(2,2));
	double psi = -atan2(m_transform(0,2), m_transform(1,2));

	double halfWidth = m_width/2;
	double halfHeight = m_height/2;

	UTxString nameStr = name();

	_ftprintf_s(moFile, L"  model %s\n", nameStr.c_str());

	//  Modelica.Mechanics.MultiBody.Parts.Body body1(m = .5, I_11 = 0.1, I_22 = 0.1, I_33 = 0.1, I_21 = 0.2, I_31 = 0.3, I_32 = 0.4, 
	//  r_CM = {1, 2, 3}, r_0(start = {2, 3, 4})) annotation(Placement(visible = true, transformation(origin = {-44, 18}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));

	_ftprintf_s(moFile, L"    Modelica.Mechanics.MultiBody.Parts.Body body1 (m = %g, I_11 = %g, I_22 = %g, I_33 = %g, I_21 = %g, I_31 = %g, I_32 = %g, "
						L"r_CM = {%g, %g, %g}, r_0(start = {%g, %g, %g}), angles_fixed = true, angles_start = {%g, %g, %g}, "
						L"sequence_start = {3, 1, 3}, useQuaternions = false, sequence_angleStates = {3, 1, 3})"
						L"annotation(Placement(visible = true, transformation(origin = {%g, %g}, extent = {{%g, %g}, {%g, %g}}, rotation = %g)));\n",
				m_mass,
				m_inertia.m_momentsOfInertia[0],  m_inertia.m_momentsOfInertia[1],  m_inertia.m_momentsOfInertia[2],
				m_inertia.m_productsOfInertia[0], m_inertia.m_productsOfInertia[1], m_inertia.m_productsOfInertia[2],
				m_cg[0], m_cg[1], m_cg[2],
				origin[0], origin[1], origin[2],
				phi, theta, psi,
				m_placement[0], m_placement[1],
				-halfWidth, -halfHeight, halfWidth, halfHeight,
				0.0);

	for (auto bodyFrame: m_bodyFrames)
		bodyFrame->write(moFile);

	_ftprintf_s(moFile, L"  equation\n");

	for (auto bodyFrame: m_bodyFrames)
		bodyFrame->connections(moFile);

	_ftprintf_s(moFile, L"    annotation(Diagram(coordinateSystem(extent = {{-100, -100}, {100, 100}}, preserveAspectRatio = true, initialScale = 0.1, grid = {2, 2})), Icon(coordinateSystem(extent = {{-100, -100}, {100, 100}}, preserveAspectRatio = true, initialScale = 0.1, grid = {2, 2}), graphics = {Bitmap(origin = {-43, 30}, extent = {{143, -130}, {-57, 70}}, imageSource = \"%S\")}));\n", m_thumbnail.c_str());

	_ftprintf_s(moFile, L"  end %s;\n", name().c_str());

	_ftprintf_s(moFile, L"  %s %s_1 annotation(Placement(visible = true, transformation(origin = {%g, %g}, extent = {{-%g, -%g}, {%g, %g}}, rotation = 0)));\n",
		nameStr.c_str(), nameStr.c_str(),
		m_placement.x, m_placement.y,
		halfWidth, halfHeight, halfWidth, halfHeight);

	return true;
}
