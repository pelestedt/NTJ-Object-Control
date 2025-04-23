<ComClass(ComClass1.ClassId, ComClass1.InterfaceId, ComClass1.EventsId)> _
Public Class ComClass1

#Region "COM GUIDs"
    ' These  GUIDs provide the COM identity for this class 
    ' and its COM interfaces. If you change them, existing 
    ' clients will no longer be able to access the class.
    Public Const ClassId As String = "c784ea1c-771c-486c-8826-10318d8f222b"
    Public Const InterfaceId As String = "96560134-6edb-45ce-b93d-5c4cd76ea61d"
    Public Const EventsId As String = "7b92f69d-f26f-40bc-85ac-e8c5d2a4071c"
#End Region

    ' A creatable COM class must have a Public Sub New() 
    ' with no parameters, otherwise, the class will not be 
    ' registered in the COM registry and cannot be created 
    ' via CreateObject.
    Public Sub New()
        MyBase.New()
    End Sub

End Class


