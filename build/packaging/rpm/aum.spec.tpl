Name:       {NAME}
Version:    {VERSION}
Release:    1
Summary:    {DESCRIPTION}
License:    LGPLv2+
Requires:   CUnit

%description
{DESCRIPTION}

%prep


%build

%install
mkdir -p %{buildroot}/usr
cp -r ./usr/include %{buildroot}%{_includedir}
cp -r ./usr/lib64 %{buildroot}/%{_libdir}

%files
%{_includedir}
%{_libdir}/libaum.so
%{_libdir}/pkgconfig/aum.pc

%changelog

