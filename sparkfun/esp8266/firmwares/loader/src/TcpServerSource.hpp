#ifndef TCPSERVERSOURCE_H
#define TCPSERVERSOURCE_H

#include "Common.hpp"
#include <stdlib.h>
/*
 *  Quick and dirty TCP server
 *
 */


namespace update {



class TcpServerSource : public Source {

private:
    enum State {S_IDLE, S_WAITING, S_ACCEPTED};

public:
    static const int DEFAULT_PORT = 8266;

    TcpServerSource(Sink& sink, AuthChecker& authChecker) :
        m_Sink(sink),
        m_AuthChecker(authChecker),
        m_State(S_IDLE),
        m_rxBuf(0),
        m_rxBufOffset(0)
    {
        
    }

    virtual Error begin(Args& args) {
        m_Port = 0;
        const char* portStr;
        if ((portStr = args.get("port")) != NULL) {
            m_Port = atoi(portStr);
        }
        if (!m_Port) {
            m_Port = DEFAULT_PORT;
        }

        err_t err;
        tcp_pcb* pcb = tcp_new();
        if (!pcb)
            return E_ALLOC_FAIL;

        err = tcp_bind(pcb, INADDR_ANY, m_Port);
        if (err != ERR_OK)
        {
            tcp_close(pcb);
            return E_BIND_FAIL;
        }

        tcp_pcb* listen_pcb = tcp_listen(pcb);
        if (!listen_pcb)
        {
            tcp_close(pcb);
            return E_ALLOC_FAIL;
        }

        m_Pcb = listen_pcb;
        tcp_arg(listen_pcb, (void*) this);
        tcp_accept(listen_pcb, &TcpServerSource::_s_accept);
        m_State = S_WAITING;
        return OK;
    }


protected:
    static int8_t _s_accept(void *arg, tcp_pcb* newpcb, int8_t err) {
        return reinterpret_cast<TcpServerSource*>(arg)->_accept(newpcb, err);
    }

    static err_t _s_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *pb, err_t err) {
        return reinterpret_cast<TcpServerSource*>(arg)->_recv(tpcb, pb, err);
    }

    static void _s_error(void *arg, err_t err) {
        reinterpret_cast<TcpServerSource*>(arg)->_error(err);
    }

    static err_t _s_poll(void *arg, struct tcp_pcb *tpcb) {
        return reinterpret_cast<TcpServerSource*>(arg)->_poll(tpcb);
    }

    static err_t _s_sent(void *arg, struct tcp_pcb *tpcb, uint16_t len) {
        return reinterpret_cast<TcpServerSource*>(arg)->_sent(tpcb, len);
    }

    int8_t _accept(tcp_pcb* apcb, int8_t err) {
        if (m_State == S_ACCEPTED) {
            tcp_abort(apcb);
            return ERR_ABRT;
        }

        m_State = S_ACCEPTED;
        tcp_arg(apcb, this);
        tcp_recv(apcb, &_s_recv);
        tcp_sent(apcb, &_s_sent);
        tcp_err(apcb, &_s_error);
        m_ClientPcb = apcb;

        tcp_accepted(m_Pcb);

        return ERR_OK;
    }

    err_t _recv(tcp_pcb* pcb, pbuf* pb, err_t err) {

        if(pb == 0) // connection closed
        {
            tcp_arg(pcb, NULL);
            tcp_sent(pcb, NULL);
            tcp_recv(pcb, NULL);
            tcp_err(pcb, NULL);
            tcp_abort(pcb);
            m_Pcb = 0;
            return ERR_ABRT;
        }

        if(m_rxBuf) {
            // there is some unread data
            // chain the new pbuf to the existing one
            // DEBUGV(":rch %d, %d\r\n", _rx_buf->tot_len, pb->tot_len);
            pbuf_cat(m_rxBuf, pb);
        } else {
            // DEBUGV(":rn %d\r\n", pb->tot_len);
            m_rxBuf = pb;
            m_rxBufOffset = 0;
        }
        // tcp_recved(pcb, received);
        // pbuf_free(pb);
        return ERR_OK;
    }

    void _error(err_t err) {
        // DEBUGV(":er %d\r\n", err);

        if(m_ClientPcb) {
            tcp_arg(m_ClientPcb, NULL);
            tcp_sent(m_ClientPcb, NULL);
            tcp_recv(m_ClientPcb, NULL);
            tcp_err(m_ClientPcb, NULL);
            err = tcp_close(m_ClientPcb);
            if(err != ERR_OK) {
                // DEBUGV(":tc err %d\r\n", err);
                tcp_abort(m_Pcb);
            }
        }
        m_ClientPcb = 0;
    }

    err_t _poll(tcp_pcb* pcb) {
        return ERR_OK;
    }

    err_t _sent(tcp_pcb* pcb, uint16_t len) {
        // DEBUGV(":sent %d\r\n", len);
        // _size_sent -= len;
        // if(_size_sent == 0 && _send_waiting) esp_schedule();
        return ERR_OK;
    }


    Sink& m_Sink;
    AuthChecker& m_AuthChecker;
    uint32_t m_Port;
    tcp_pcb* m_Pcb;
    tcp_pcb* m_ClientPcb;
    State m_State;
    pbuf* m_rxBuf;
    size_t m_rxBufOffset;
};



} // namespace update

#endif //TCPSERVERSOURCE_H

